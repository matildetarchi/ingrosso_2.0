//
// Created by Andrea Lipperi on 04/05/23.
//

#include "OrderHistoryForClientPage.h"

#include "SingleOrderClientPage.h"


const long OrderHistoryForClientPage::IdButtonCancel =::wxNewId();
const long OrderHistoryForClientPage::IdButtonView =::wxNewId();
const long OrderHistoryForClientPage::IdButtonBack =::wxNewId();

BEGIN_EVENT_TABLE (OrderHistoryForClientPage, wxDialog)
                EVT_BUTTON(IdButtonCancel, OrderHistoryForClientPage::CancelOrder)
                EVT_BUTTON(IdButtonView, OrderHistoryForClientPage::ViewOrder)
                EVT_BUTTON(IdButtonBack, OrderHistoryForClientPage::ComeBack)

END_EVENT_TABLE()

OrderHistoryForClientPage::OrderHistoryForClientPage(Engine *e, const wxString &title, int control): engine(e), ctrl(control),
        wxDialog(nullptr, -1, title, wxPoint(-1, -1), wxSize(600, 350)) {

    client = engine->get_client();
    username = client->get_username();


    db_order = engine->get_db_order();

    int row = db_order->select_count_for_client();
    int row_op = db_order->select_count_for_client_onlyp();

    grid = new wxGrid(this, wxID_ANY,wxDefaultPosition, wxSize(450,300));
    if (ctrl==0) {
        grid->CreateGrid(row_op, 2);
        grid->SetColLabelValue(0, "Code order");
        grid->SetColLabelValue(1, "Date");

    } else {
        grid->CreateGrid(row, 3);
        grid->SetColLabelValue(0, "Code order");
        grid->SetColLabelValue(1, "Date");
        grid->SetColLabelValue(2, "Status");

    }
    orders_list = client->get_order_list();
    order = orders_list->get_orders();

    if(ctrl == 0) {
        int i = 0;
        int j = 0;
        while(i < row) {
            if(order[i]->get_status() == "S") {
                shared_ptr<Date> d = order[i]->get_date();
                std::string date = d->to_string("%d/%m/%Y");
                int id_o = order[i]->get_id();
                string id_order = (to_string(id_o));
                shared_ptr<Order> o = make_shared<Order>(id_o, "S", username);
                o->set_date(d);
                order_op.push_back(o);

                grid->SetReadOnly(j, 0, true);
                grid->SetCellValue(j, 0, id_order);
                grid->SetReadOnly(j, 1, true);
                grid->SetCellValue(j, 1, date);
                j++;
                i++;
            } else
                i++;
        }
    } else {
        int i = 0;
        while( i < row) {
            shared_ptr<Date> d = order[i]->get_date();
            std::string date = d->to_string("%d/%m/%Y");
            string status = order[i]->get_status();
            int id_o = order[i]->get_id();
            string id_order = (to_string(id_o));

            grid->SetReadOnly(i, 0, true);
            grid->SetCellValue(i, 0, id_order);
            grid->SetReadOnly(i, 1, true);
            grid->SetCellValue(i, 1, date);
            grid->SetReadOnly(i, 2, true);
            grid->SetCellValue(i, 2, status);
            i++;
        }
    }

    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();


    Cancel = new wxButton(this, IdButtonCancel, _T ("Cancel OrderProduct"), wxDefaultPosition, wxDefaultSize, 0);
    View = new wxButton(this, IdButtonView, _T ("View"), wxDefaultPosition, wxDefaultSize, 0);
    Back = new wxButton(this, IdButtonBack, _T ("Back"), wxDefaultPosition, wxDefaultSize, 0);
    sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer_vertical = new wxBoxSizer(wxVERTICAL);

    sizer->Add(grid, 1,  wxALL, 5);
    sizer_vertical->Add(Cancel, 1,  wxALL, 5);
    sizer_vertical->Add(View, 1,  wxALL, 5);
    sizer_vertical->Add(Back, 1,  wxALL, 5);
    sizer->Add(sizer_vertical, 1);

    SetSizer(sizer);

    Centre();


}

void OrderHistoryForClientPage::CancelOrder(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (int i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }

        string status = order[row]->get_status();
        int id_order = order[row]->get_id();

        if (ctrl == 1 && status != "S") {
            wxMessageBox("The one you choosed it's already confirmed or denied, you can't cancel it", "Error",
                         wxICON_ERROR);
        } else {
            db_order->cancel_order(id_order);
            grid->DeleteRows(row);
        }
    }
}
void OrderHistoryForClientPage::ViewOrder(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int code;
        if(ctrl == 1) {
            int row;
            for (int i = 0; i < selectedRows.GetCount(); i++) {
                row = selectedRows[i];
            }

            code = order[row]->get_id();
        } else {
            int row_op = 0;
            for (int i = 0; i < selectedRows.GetCount(); i++) {
                row_op = selectedRows[i];
            }

            code = order_op[row_op]->get_id();

        }
        auto *view = new SingleOrderClientPage(engine, _T("ORDER LIST"), code);
        view->Show(TRUE);
    }

}

void OrderHistoryForClientPage::ComeBack(wxCommandEvent &event) {
    Close();
}
