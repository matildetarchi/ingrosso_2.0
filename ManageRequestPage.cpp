//
// Created by Andrea Lipperi on 21/04/23.
//

#include "ManageRequestPage.h"


const long ManageRequestPage::IdButtonConfirm =::wxNewId();
const long ManageRequestPage::IdButtonDeny =::wxNewId();
const long ManageRequestPage::IdButtonView =::wxNewId();

BEGIN_EVENT_TABLE (ManageRequestPage, wxDialog)
                EVT_BUTTON(IdButtonConfirm, ManageRequestPage::OnConfirm)
                EVT_BUTTON(IdButtonDeny, ManageRequestPage::OnDeny)
                EVT_BUTTON(IdButtonView, ManageRequestPage::ViewOrder)
END_EVENT_TABLE()

ManageRequestPage::ManageRequestPage(Engine* e, const wxString &title, int control): engine(e),
        wxDialog(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {



    prov = engine->get_prov();
    db_order = engine->get_db_order();

   /* wxStaticText *order_txt = new wxStaticText(this, -1, wxT("OrderProduct By"));
    wxString myString[]={"Code OrderProduct", "Customer Name", "Date OrderProduct"};
    choiceOrder=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceOrder->Append("Select");
    choiceOrder->Append(3,myString);
    choiceOrder->Bind(wxEVT_CHOICE, &ManageRequestPage::OnChoice, this);*/


    int row = db_order->select_count_for_provider();
    grid = new wxGrid(this, wxID_ANY);

    grid->CreateGrid(row, 4);
    grid->SetColLabelValue(0, "Code order");
    grid->SetColLabelValue(1, "Customer");
    grid->SetColLabelValue(2, "Date");
    grid->SetColLabelValue(3, "Status");

    orders_list= prov->get_order_list();
    order= orders_list->get_orders();

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


    Confirm=new wxButton (this,IdButtonConfirm,_T ("Confirm OrderProduct"),wxDefaultPosition,wxDefaultSize,0);
    Deny=new wxButton (this,IdButtonDeny,_T ("Deny OrderProduct"),wxDefaultPosition,wxDefaultSize,0);
    View=new wxButton (this,IdButtonView,_T ("View"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxVERTICAL);

    //sizer->Add(order_txt, 0, wxALL, 5);
    sizer->Add(choiceOrder, 0, wxALL, 5);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Confirm, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Deny, 1, wxEXPAND | wxALL, 5);
    sizer->Add(View, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();


}

void ManageRequestPage::OnConfirm(wxCommandEvent &event) {

    wxArrayInt selectedRows = grid->GetSelectedRows();
    int row;
    size_t i = 0;
    while (i == selectedRows.GetCount()) {
        i++;
    }
    row = selectedRows[i];

    string status =order[row]->get_status();
    int id_order= order[row]->get_id();

    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else if (ctrl == 1 && status != "Pending") {
        wxMessageBox("The one you choosed it's already confirmed or denied", "Error", wxICON_ERROR);
    } else {

        prov->accept_order(id_order);

        if (ctrl == 0) {
            grid->DeleteRows(row);
        } else {
            grid->SetCellValue(row, 3, "Accepted");
            }
        }
}

void ManageRequestPage::OnDeny(wxCommandEvent &event) {
    wxArrayInt selectedRows = grid->GetSelectedRows();
    int row;
    size_t i = 0;
    while (i == selectedRows.GetCount()) {
        i++;
    }
    row = selectedRows[i];
    string status =order[row]->get_status();
    int id_order= order[row]->get_id();

    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else if (ctrl==1 && status!="Pending") {
        wxMessageBox("The one you choosed it's already confirmed or denied", "Error", wxICON_ERROR);
    } else {

        prov->denied_order(id_order);

        if (ctrl==0) {
            grid->DeleteRows(row);
        } else {
            grid->SetCellValue(row, 3, "Denied");
        }
    }
}
void ManageRequestPage::ViewOrder(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else {
        std::string code;
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        size_t i = 0;
        while (i == selectedRows.GetCount()) {
            i++;
        }
        row = selectedRows[i];

        int code_order= order[row]->get_id();
        string id_order(to_string(code_order));
        SingleOrderProviderPage *view = new SingleOrderProviderPage(engine, _T("ORDER LIST"), id_order);
        view->Show(TRUE);
    }

}

/*void ManageRequestPage::OnChoice(wxCommandEvent& event) {
    OrderProduct table;
    string order_choice=event.GetString().ToStdString();
    mat_order=table.select_for_provider(username,ctrl,order_choice);
    for (int i = 0; i < table.select_count_for_provider(username,ctrl); i++) {
        if (ctrl==0) {
            for (int col = 0; col < 3; col++) {
                grid->SetReadOnly(i, col, true);
                grid->SetCellValue(i, col, mat_order[i][col]);
            }
        } else {
            for (int col = 0; col < 4; col++) {
                grid->SetReadOnly(i, col, true);
                grid->SetCellValue(i, col, mat_order[i][col]);
            }
        }
    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();
}
*/