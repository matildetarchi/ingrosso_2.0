//
// Created by Andrea Lipperi on 03/04/23.
//

#include "FavouritesListPage.h"


const long FavouritesListPage::IdButtonRemove =::wxNewId();
const long FavouritesListPage::IdButtonCart =::wxNewId();
const long FavouritesListPage::IdButtonComeBack =::wxNewId();
const long FavouritesListPage::IdButtonInsert =::wxNewId();

BEGIN_EVENT_TABLE (FavouritesListPage, wxFrame)
                EVT_BUTTON(IdButtonRemove, FavouritesListPage::IsRemove)
                EVT_BUTTON(IdButtonCart, FavouritesListPage::IsCart)
                EVT_BUTTON(IdButtonInsert, FavouritesListPage::IsInsert)
                EVT_BUTTON(IdButtonComeBack, FavouritesListPage::ComeBack)

END_EVENT_TABLE()

FavouritesListPage::FavouritesListPage(Engine *e, const wxString &title): engine(e),
                   wxFrame(nullptr, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {


    client = engine->get_client();
    username = client->get_username();
    db_cart = engine->get_db_cart();
    cart = client->get_cart();
    db_fav = engine->get_db_fav();
    fav = client->get_fav();

    if (fav != nullptr) {
        prod_list = fav->get_products();

        int row = db_fav->select_count_of_prod();

        grid = new wxGrid(this, wxID_ANY);
        grid->CreateGrid(row, 3);
        grid->SetColLabelValue(0, "Name Product");
        grid->SetColLabelValue(1, "Price");
        grid->SetColLabelValue(2, "Provider Name");

        for (int i = 0; i < row; i++) {

            string name_prod = prod_list[i]->get_desc();
            double pr = prod_list[i]->get_price();
            string price = (to_string(pr));
            string name_prov = prod_list[i]->get_username_prov();

            grid->SetReadOnly(i, 0, true);
            grid->SetCellValue(i, 0, name_prod);
            grid->SetReadOnly(i, 1, true);
            grid->SetCellValue(i, 1, price);
            grid->SetReadOnly(i, 2, true);
            grid->SetCellValue(i, 2, name_prov);

        }
    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();

    Remove = new wxButton(this,IdButtonRemove,_T ("Remove"),wxDefaultPosition,wxDefaultSize,0);
    Cart_button = new wxButton(this,IdButtonCart,_T ("Add to Cart"),wxDefaultPosition,wxDefaultSize,0);
    Back = new wxButton(this,IdButtonComeBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer_vertical = new wxBoxSizer(wxVERTICAL);

    sizer->Add(grid, 1,  wxALL, 5);
    sizer_vertical->Add(Remove, 1,  wxALL, 5);
    sizer_vertical->Add(Cart_button, 1,  wxALL, 5);
    sizer_vertical->Add(Back, 1,  wxALL, 5);
    sizer->Add(sizer_vertical,1);
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
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        control = 0;
        sizer_vertical->Hide(Remove);
        sizer_vertical->Hide(Cart_button);
        auto *q = new wxStaticText(this, -1, wxT("Insert Quantity"));
        sizer_vertical->Add(q, 0,  wxALL, 5);
        spinCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);
        sizer_vertical->Add(spinCtrl, 0,  wxALL, 5);
        Insert = new wxButton(this, IdButtonInsert, _T ("Insert"), wxDefaultPosition, wxDefaultSize, 0);
        sizer_vertical->Add(Insert, 0,  wxALL, 5);
        wxSize currentSize = GetSize();
        int newWidth = currentSize.GetWidth() + 1;
        int newHeight = currentSize.GetHeight() + 1;
        SetSize(newWidth, newHeight);

    }
}

void FavouritesListPage::ComeBack(wxCommandEvent &event) {
    Close();
}

void FavouritesListPage::IsInsert(wxCommandEvent &event) {
    int row;
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        if (spinCtrl->GetValue() < 1) {
            wxMessageBox("Insert a valid quantity", "Error", wxICON_ERROR);
        } else {
            wxArrayInt selectedRows = grid->GetSelectedRows();

            for (size_t i = 0; i < selectedRows.GetCount(); i++) {
                row = selectedRows[i];
            }

            bool ctrl = db_cart->control_if_exist(prod_list[row]);
            quantity = spinCtrl->GetValue();
            prod_l = cart->get_products();
            if(quantity <= prod_list[row]->get_q_available()) {
                if(ctrl) {
                    if (control == 0) {
                        wxMessageBox("Product already in cart, click againg in insert if you want to add this quantity", "Error", wxICON_ERROR);
                    } else {
                        int i = 0;
                        int count = 0;
                        while(i < prod_l.size() && count == 0) {
                            string desc_cart = prod_l[i]->get_desc();
                            string desc_fav = prod_list[row]->get_desc();
                            string prov_cart = prod_l[i]->get_username_prov();
                            string prov_fav = prod_list[row]->get_username_prov();
                            bool isEqual_desc = desc_cart == desc_fav;
                            bool isEqual_us = prov_cart == prov_fav;
                            if (isEqual_desc && isEqual_us) {
                                count = 1;
                            } else {
                                i++;
                            }
                        }
                        int q = prod_l[i]->get_quantity();
                        int new_quantity = q + quantity;
                        int id_cart = db_cart->select_id_cart(prod_l[i]->get_desc(),prod_l[i]->get_username_prov());
                        int control_q = new_quantity+prod_l[i]->get_quantity();
                        if (control_q <= prod_list[i]->get_q_available()) {
                            prod_l[i]->set_quantity(new_quantity);
                            db_cart->change_quantity(id_cart, new_quantity);
                            cart->set_prod(prod_l);
                            wxMessageBox("Insert gone well", "", wxICON_ERROR);
                        } else {
                            wxMessageBox("Quantity not available", "Error", wxICON_ERROR);
                        }
                    }
                    control = 1;

                } else {
                    prod_list[row]->set_quantity(quantity);
                    client->add_to_cart(prod_list[row]);
                    db_cart->add_to_db();
                    wxMessageBox("Insert gone well", "", wxICON_ERROR);
                }

            } else {
                wxMessageBox("Quantity not available", "Error", wxICON_ERROR);
            }
        }
    }
}