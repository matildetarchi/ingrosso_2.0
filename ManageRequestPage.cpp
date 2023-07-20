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

ManageRequestPage::ManageRequestPage(const wxString &title, int control):
        wxDialog(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {
    ctrl=control;
    username=GlobalVariables::GetInstance().GetValueUsername();
    wxStaticText *order_txt = new wxStaticText(this, -1, wxT("OrderProduct By"));
    wxString myString[]={"Code OrderProduct", "Customer Name", "Date OrderProduct"};
    choiceOrder=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceOrder->Append("Select");
    choiceOrder->Append(3,myString);
    choiceOrder->Bind(wxEVT_CHOICE, &ManageRequestPage::OnChoice, this);

    OrderProduct order;
    int row = order.select_count_for_provider(username,ctrl);
    grid = new wxGrid(this, wxID_ANY);
    if (ctrl==0) {
        grid->CreateGrid(row, 3);
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
    mat_order=order.select_for_provider(username,ctrl);


    for (int i = 0; i < order.select_count_for_provider(username,ctrl); i++) {
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


    Confirm=new wxButton (this,IdButtonConfirm,_T ("Confirm OrderProduct"),wxDefaultPosition,wxDefaultSize,0);
    Deny=new wxButton (this,IdButtonDeny,_T ("Deny OrderProduct"),wxDefaultPosition,wxDefaultSize,0);
    View=new wxButton (this,IdButtonView,_T ("View"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(order_txt, 0, wxALL, 5);
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
    for (size_t i = 0; i < selectedRows.GetCount(); i++) {
        row = selectedRows[i];
    }
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else if (ctrl==1 && mat_order[row][3]!="Pending") {
        wxMessageBox("The one you choosed it's already confirmed or denied", "Error", wxICON_ERROR);
    } else {
        OrderProduct table;
        string new_status;
        new_status="A";
        table.changeStatus(username,mat_order[row][0],new_status);
        if (ctrl==0) {
            grid->DeleteRows(row);
        } else {
            grid->SetCellValue(row, 3, "Accepted");
        }
    }
}
void ManageRequestPage::OnDeny(wxCommandEvent &event) {
    wxArrayInt selectedRows = grid->GetSelectedRows();
    int row;
    for (size_t i = 0; i < selectedRows.GetCount(); i++) {
        row = selectedRows[i];
    }
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else if (ctrl==1 && mat_order[row][3]!="Pending") {
        wxMessageBox("The one you choosed it's already confirmed or denied", "Error", wxICON_ERROR);
    } else {
        OrderProduct table;
        string new_status;
        new_status="D";
        table.changeStatus(username,mat_order[row][0],new_status);
        if (ctrl==0) {
            grid->DeleteRows(row);
        } else {
            grid->SetCellValue(row, 3, "Denied");
        }
    }
}
void ManageRequestPage::ViewOrder(wxCommandEvent &event) {
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a order", "Error", wxICON_ERROR);
    } else {
        std::string code;
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        code = mat_order[row][0];
        SingleOrderProviderPage *view = new SingleOrderProviderPage(_T("ORDER LIST"), code);
        view->Show(TRUE);
    }

}

void ManageRequestPage::OnChoice(wxCommandEvent& event) {
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