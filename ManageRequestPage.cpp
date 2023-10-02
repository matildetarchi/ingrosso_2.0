//
// Created by Andrea Lipperi on 21/04/23.
//

#include "ManageRequestPage.h"


const long ManageRequestPage::IdButtonConfirm =::wxNewId();
const long ManageRequestPage::IdButtonDeny =::wxNewId();
const long ManageRequestPage::IdButtonView =::wxNewId();
const long ManageRequestPage::IdButtonBack =::wxNewId();


BEGIN_EVENT_TABLE (ManageRequestPage, wxDialog)
                EVT_BUTTON(IdButtonConfirm, ManageRequestPage::OnConfirm)
                EVT_BUTTON(IdButtonDeny, ManageRequestPage::OnDeny)
                EVT_BUTTON(IdButtonView, ManageRequestPage::ViewOrder)
                EVT_BUTTON(IdButtonBack, ManageRequestPage::ComeBack)
END_EVENT_TABLE()

ManageRequestPage::ManageRequestPage(Engine* e, const wxString &title, int control): engine(e), ctrl(control),
        wxDialog(nullptr, -1, title, wxPoint(-1, -1), wxSize(600, 350)) {


    prov = engine->get_prov();
    db_order = engine->get_db_order();


    int row_op = db_order->select_count_for_provider_onlyp(ctrl);
    int row = db_order->select_count_for_provider();
    grid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(450,300));


    orders_list = prov->get_order_list();
    order = orders_list->get_orders();

    if (ctrl==0) {
        grid->CreateGrid(row_op, 3);
        grid->SetColLabelValue(0, "Code order");
        grid->SetColLabelValue(1, "Customer");
        grid->SetColLabelValue(2, "Date");

    } else {
        grid->CreateGrid(row, 4);
        grid->SetColLabelValue(0, "Code order");
        grid->SetColLabelValue(1, "Customer");
        grid->SetColLabelValue(2, "Date");
        grid->SetColLabelValue(3, "Status");
    }

    if(ctrl == 0) {
        int i = 0;
        int j = 0;
        while(i < row) {
            if(order[i]->get_status() == "S") {
                shared_ptr<Date> d = order[i]->get_date();
                std::string date = d->to_string("%d/%m/%Y");
                string us_client = order[i]->get_us_client();
                int id_o = order[i]->get_id();
                string id_order = (to_string(id_o));
                shared_ptr<Order> o = make_shared<Order>(id_o, "S", us_client);
                o->set_date(d);
                order_op.push_back(o);

                grid->SetReadOnly(j, 0, true);
                grid->SetCellValue(j, 0, id_order);
                grid->SetReadOnly(j, 1, true);
                grid->SetCellValue(j, 1, us_client);
                grid->SetReadOnly(j, 2, true);
                grid->SetCellValue(j, 2, date);
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
            string us_client = order[i]->get_us_client();
            int id_o = order[i]->get_id();
            string id_order = (to_string(id_o));

            grid->SetReadOnly(i, 0, true);
            grid->SetCellValue(i, 0, id_order);
            grid->SetReadOnly(i, 1, true);
            grid->SetCellValue(i, 1, us_client);
            grid->SetReadOnly(i, 2, true);
            grid->SetCellValue(i, 2, date);
            grid->SetReadOnly(i, 3, true);
            grid->SetCellValue(i, 3, status);
            i++;
        }
    }

    sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer_vertical = new wxBoxSizer(wxVERTICAL);
    View = new wxButton (this,IdButtonView,_T ("View"),wxDefaultPosition,wxDefaultSize,0);
    Back = new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    if(ctrl == 0){

        grid->SetSelectionMode(wxGrid::wxGridSelectRows);
        grid->AutoSize();

        Confirm=new wxButton (this,IdButtonConfirm,_T ("Confirm OrderProduct"),wxDefaultPosition,wxDefaultSize,0);
        Deny=new wxButton (this,IdButtonDeny,_T ("Deny OrderProduct"),wxDefaultPosition,wxDefaultSize,0);

        sizer->Add(grid, 1,  wxALL, 5);
        sizer_vertical->Add(Confirm, 1,  wxALL, 5);
        sizer_vertical->Add(Deny, 1,  wxALL, 5);
        sizer_vertical->Add(View, 1,  wxALL, 5);
        sizer_vertical->Add(Back, 1,  wxALL, 5);
        sizer->Add(sizer_vertical,1);
    }
    else {
        grid->SetSelectionMode(wxGrid::wxGridSelectRows);
        grid->AutoSize();

        sizer_vertical->Add(View, 1,  wxALL, 5);
        sizer_vertical->Add(Back, 1,  wxALL, 5);
        sizer->Add(grid, 1,  wxALL, 5);
        sizer->Add(sizer_vertical,1);
    }

    SetSizer(sizer);

    Centre();


}

void ManageRequestPage::OnConfirm(wxCommandEvent &event) {

    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    }
    wxArrayInt selectedRows = grid->GetSelectedRows();
    int row;
    int id_order;
    if(ctrl == 1) {

        for (int i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }

        id_order = order[row]->get_id();
    } else {
        int row_op = 0;
        for (int i = 0; i < selectedRows.GetCount(); i++) {
            row_op = selectedRows[i];
        }

        id_order = order_op[row_op]->get_id();
    }

    db_order->change_status("A", id_order);

    if (ctrl==0)
        grid->DeleteRows(row);
    else
        grid->SetCellValue(row, 3, "Accepted");
}

void ManageRequestPage::OnDeny(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    }
    wxArrayInt selectedRows = grid->GetSelectedRows();
    int row;
    int id_order;
    if(ctrl == 1) {

        for (int i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }

        id_order = order[row]->get_id();
    } else {
        int row_op = 0;
        for (int i = 0; i < selectedRows.GetCount(); i++) {
            row_op = selectedRows[i];
        }

        id_order = order_op[row_op]->get_id();
    }

    db_order->change_status("D", id_order);

    if (ctrl==0)
        grid->DeleteRows(row);
    else
        grid->SetCellValue(row, 3, "Denied");

}

void ManageRequestPage::ViewOrder(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int code_order;
        if(ctrl == 1) {
            int row;
            for (int i = 0; i < selectedRows.GetCount(); i++) {
                row = selectedRows[i];
            }

            code_order = order[row]->get_id();
        } else {
            int row_op = 0;
            for (int i = 0; i < selectedRows.GetCount(); i++) {
                row_op = selectedRows[i];
            }

            code_order = order_op[row_op]->get_id();

        }
        auto *view = new SingleOrderProviderPage(engine, _T("ORDER LIST"), code_order);
        view->Show(TRUE);
    }

}

void ManageRequestPage::ComeBack(wxCommandEvent& event){
    Close();
}