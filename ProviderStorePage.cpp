//
// Created by Andrea Lipperi on 02/05/23.
//


#include "ProviderStorePage.h"

#define colonne 4
const long ProviderStorePage::IdButtonDelete =::wxNewId();
const long ProviderStorePage::IdButtonBack =::wxNewId();
const long ProviderStorePage::IdButtonModify =::wxNewId();

BEGIN_EVENT_TABLE (ProviderStorePage, wxDialog)
                EVT_BUTTON(IdButtonDelete, ProviderStorePage::DeleteProduct)
                EVT_BUTTON(IdButtonModify, ProviderStorePage::ModifyProduct)
                EVT_BUTTON(IdButtonBack, ProviderStorePage::ComeBack)

END_EVENT_TABLE()

ProviderStorePage::ProviderStorePage(const wxString &title):
        wxDialog(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {

    username=GlobalVariables::GetInstance().GetValueUsername();

    wxStaticText *order = new wxStaticText(this, -1, wxT("OrderProduct By"));
    wxString myString[]={"Name Product", "Price", "Quantity Available"};
    choiceOrder=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceOrder->Append("Select");
    choiceOrder->Append(3,myString);
    choiceOrder->Bind(wxEVT_CHOICE, &ProviderStorePage::OnChoice, this);

    StoreProduct store;
    int row = store.select_count_for_prov(username);

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 3);
    grid->SetColLabelValue(0, "Name Product");
    grid->SetColLabelValue(1, "Price");
    grid->SetColLabelValue(2, "Quantity Available");

    mat_store=store.select_for_prov(username);

    for (int i = 0; i < store.select_count_for_prov(username); i++) {
        for (int col = 0; col < 3; col++) {
            grid->SetReadOnly(i, col, true);
            grid->SetCellValue(i, col,  mat_store[i][col]);
        }
    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();


    Delete=new wxButton (this,IdButtonDelete,_T ("Remove"),wxDefaultPosition,wxDefaultSize,0);
    Modify=new wxButton (this,IdButtonModify,_T ("Modify"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(order);
    sizer->Add(choiceOrder, 0, wxALL, 5);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Delete, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Modify, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Back, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();


}
void ProviderStorePage::ComeBack(wxCommandEvent &event) {

    Close();

}

void ProviderStorePage::DeleteProduct(wxCommandEvent &event) {
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        StoreProduct store;
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        if (!store.remove(stoi(mat_store[row][3]))) {
            wxMessageBox("You can't remove this product from your store because is in someone's cart or favourites list or not accepted/denied order", "Error", wxICON_ERROR);
        } else {
            grid->DeleteRows(row);
        }
    }
}
void ProviderStorePage::ModifyProduct(wxCommandEvent &event) {
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        StoreProduct store;
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        ModifyProductPage *mod = new ModifyProductPage(_T("MODIFY PRODUCT"), stoi(mat_store[row][3]));
        mod->Show(TRUE);
    }
}

void ProviderStorePage::OnChoice(wxCommandEvent& event) {
    StoreProduct store;

    string order=event.GetString().ToStdString();

    mat_store=store.select_for_prov(username, order);

    for (int i = 0; i < store.select_count_for_prov(username); i++) {
        for (int col = 0; col < 3; col++) {
            grid->SetReadOnly(i, col, true);
            grid->SetCellValue(i, col,  mat_store[i][col]);
        }
    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();
}