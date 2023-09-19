//
// Created by Andrea Lipperi on 03/04/23.
//

#include "FavouritesListPage.h"


const long FavouritesListPage::IdButtonRemove =::wxNewId();
const long FavouritesListPage::IdButtonCart =::wxNewId();
const long FavouritesListPage::IdButtonComeBack =::wxNewId();

BEGIN_EVENT_TABLE (FavouritesListPage, wxFrame)
                EVT_BUTTON(IdButtonRemove, FavouritesListPage::IsRemove)
                EVT_BUTTON(IdButtonCart, FavouritesListPage::IsCart)
                EVT_BUTTON(IdButtonComeBack, FavouritesListPage::ComeBack)
END_EVENT_TABLE()

FavouritesListPage::FavouritesListPage(Engine *e, const wxString &title): engine(e),
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {

    client = engine->get_client();
    username = client->get_username();
    db_cart = engine->get_db_cart();
    cart = client->get_cart();
    db_fav = engine->get_db_fav();
    fav = client->get_fav();
    prod_list = fav->get_products();

    int row = db_fav->select_count_of_prod();

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 3);
    grid->SetColLabelValue(0, "Name Product");
    grid->SetColLabelValue(1, "Price");
    grid->SetColLabelValue(2, "Provider Name");

    for (int i = 0; i < row; i++) {

        string name_prod = prod_list[i]->get_desc();
        int p = prod_list[i]->get_price();
        string price(to_string(p));
        string name_prov = prod_list[i]->get_username_prov();

        grid->SetReadOnly(i, 0, true);
        grid->SetCellValue(i, 0, name_prod);
        grid->SetReadOnly(i, 1, true);
        grid->SetCellValue(i, 1, price);
        grid->SetReadOnly(i, 2, true);
        grid->SetCellValue(i, 2, name_prov);

    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();

    Remove = new wxButton(this,IdButtonRemove,_T ("Remove"),wxDefaultPosition,wxDefaultSize,0);
    Cart_button = new wxButton(this,IdButtonCart,_T ("Add to Cart"),wxDefaultPosition,wxDefaultSize,0);
    Back = new wxButton(this,IdButtonComeBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Remove, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Cart_button, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Back, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);


    Centre();


}

void FavouritesListPage::IsRemove(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        int id = prod_list[row]->get_id_store();
        db_fav->remove_prod(id);
        client->remove_from_fav(id);
        grid->DeleteRows(row);
    }
}

void FavouritesListPage::IsCart(wxCommandEvent &event) {

    int row = db_fav->select_count_of_prod();
    int i = 0;
    while (i<row) {
        client->add_to_cart(prod_list[i]);
        db_cart->add_to_db();
        i++;
    }
}

void FavouritesListPage::ComeBack(wxCommandEvent &event) {
    Close();
}
