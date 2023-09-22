//
// Created by Andrea Lipperi on 04/05/23.
//

#include "OrderHistoryForClientPage.h"

#include "SingleOrderClientPage.h"


const long OrderHistoryForClientPage::IdButtonCancel =::wxNewId();
const long OrderHistoryForClientPage::IdButtonView =::wxNewId();

BEGIN_EVENT_TABLE (OrderHistoryForClientPage, wxDialog)
                EVT_BUTTON(IdButtonCancel, OrderHistoryForClientPage::CancelOrder)
                EVT_BUTTON(IdButtonView, OrderHistoryForClientPage::ViewOrder)

END_EVENT_TABLE()

OrderHistoryForClientPage::OrderHistoryForClientPage(Engine *e, const wxString &title): engine(e),
        wxDialog(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {



    client = engine->get_client();
    username = client->get_username();
    db_order = engine->get_db_order();

   /* wxStaticText *order_txt = new wxStaticText(this, -1, wxT("OrderProduct By"));
    wxString myString[]={"Code OrderProduct", "Provider Name", "Date OrderProduct"};
    choiceOrder=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceOrder->Append("Select");
    choiceOrder->Append(3,myString);
    choiceOrder->Bind(wxEVT_CHOICE, &OrderHistoryForClientPage::OnChoice, this);*/


    int row = db_order->select_count_for_client();

    grid = new wxGrid(this, wxID_ANY);
    if (ctrl==0) {
        grid->CreateGrid(row, 3);
        grid->SetColLabelValue(0, "Code order");
        grid->SetColLabelValue(1, "Provider");
        grid->SetColLabelValue(2, "Date");
    } else {

        grid->CreateGrid(row, 4);
        grid->SetColLabelValue(0, "Code order");
        grid->SetColLabelValue(1, "Provider");
        grid->SetColLabelValue(2, "Date");
        grid->SetColLabelValue(3, "Status");

    }

    orders_list= client->get_order_list();

    if(orders_list != NULL) {
        order = orders_list->get_orders();
    }
    for (int i = 0; i < row; i++) {
        shared_ptr<Date> d= order[i]->get_date();
        std::string date = d->to_string("%d/%m/%Y");
        string status= order[i]->get_status();
        string us_client= order[i]->get_us_client();
        int id_o= order[i]->get_id();
        string id_order(to_string(id_o));

        if (ctrl==0) {
            grid->SetReadOnly(i, 0, true);
            grid->SetCellValue(i, 0, id_order);
            grid->SetReadOnly(i, 1, true);
            grid->SetCellValue(i, 1, us_client);
            grid->SetReadOnly(i, 2, true);
            grid->SetCellValue(i, 2, date);
        }
         else {
            grid->SetReadOnly(i, 0, true);
            grid->SetCellValue(i,0, id_order);
            grid->SetReadOnly(i, 1, true);
            grid->SetCellValue(i,1, us_client);
            grid->SetReadOnly(i, 2, true);
            grid->SetCellValue(i,2, date);
            grid->SetReadOnly(i, 3, true);
            grid->SetCellValue(i,3, status);
            }
        }

    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();


    Cancel=new wxButton (this,IdButtonCancel,_T ("Cancel OrderProduct"),wxDefaultPosition,wxDefaultSize,0);
    View=new wxButton (this,IdButtonView,_T ("View"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxVERTICAL);

    //sizer->Add(order_txt, 0, wxALL, 5);
    sizer->Add(choiceOrder, 0, wxALL, 5);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Cancel, 1, wxEXPAND | wxALL, 5);
    sizer->Add(View, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();


}

void OrderHistoryForClientPage::CancelOrder(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        size_t i = 0;
        while (i == selectedRows.GetCount()) {
            i++;
        }
        row = selectedRows[i];
        string status = order[row]->get_status();
        int id_order = order[row]->get_id();

        if (ctrl == 1 && status != "Pending") {
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
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        int code = order[row]->get_id();
        SingleOrderClientPage *view = new SingleOrderClientPage(engine, _T("ORDER LIST"), to_string(code));
        view->Show(TRUE);
    }

}
