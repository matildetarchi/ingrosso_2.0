//
// Created by Andrea Lipperi on 02/05/23.
//

#include "ProviderStorePage.h"

const long ProviderStorePage::IdButtonDelete =::wxNewId();
const long ProviderStorePage::IdButtonBack =::wxNewId();
const long ProviderStorePage::IdButtonModify =::wxNewId();

BEGIN_EVENT_TABLE (ProviderStorePage, wxDialog)
                EVT_BUTTON(IdButtonDelete, ProviderStorePage::DeleteProduct)
                EVT_BUTTON(IdButtonModify, ProviderStorePage::ModifyProduct)
                EVT_BUTTON(IdButtonBack, ProviderStorePage::ComeBack)
END_EVENT_TABLE()

ProviderStorePage::ProviderStorePage(Engine *e, const wxString &title): engine(e),
        wxDialog(nullptr, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {

    prov = engine->get_prov();
    username = prov->get_username();

    store = prov->get_store();

    db_store= engine->get_db_store();
    int row = db_store->select_count_for_provider();

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 3);
    grid->SetColLabelValue(0, "Name Product");
    grid->SetColLabelValue(1, "Price");
    grid->SetColLabelValue(2, "Quantity Available");

    prod_list = store->get_products();


    for (int i = 0; i < row ; i++) {
      string name_prod= prod_list[i]->get_desc();
      float p= prod_list[i]->get_price();
      string price(to_string(p));
      int a_q= prod_list[i]->get_q_available();
      string available_q(to_string(a_q));

        grid->SetReadOnly(i, 0, true);
        grid->SetCellValue(i, 0, name_prod);
        grid->SetReadOnly(i, 1, true);
        grid->SetCellValue(i, 1, price);
        grid->SetReadOnly(i, 2, true);
        grid->SetCellValue(i, 2, available_q);
    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();


    Delete = new wxButton (this,IdButtonDelete,_T ("Remove"),wxDefaultPosition,wxDefaultSize,0);
    Modify = new wxButton (this,IdButtonModify,_T ("Modify"),wxDefaultPosition,wxDefaultSize,0);
    Back = new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxVERTICAL);

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
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {

        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        size_t i = 0;
        while (i == selectedRows.GetCount()) {
            i++;
        }
        row = selectedRows[i];
        int id_prod= prod_list[i]->get_id_store();
        if(!db_store->remove_from_db(id_prod)){
            wxMessageBox("You can't remove this product from your store because is in someone's cart or favourites list or not accepted/denied order",
                         "Error", wxICON_ERROR);
        } else {
            grid->DeleteRows(row);
        }
    }
}
void ProviderStorePage::ModifyProduct(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {

        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row = 0;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        int id_prod= prod_list[row]->get_id_store();
        auto *mod = new ModifyProductPage(engine, _T("MODIFY PRODUCT"), id_prod);
        mod->Show(TRUE);
    }
}
