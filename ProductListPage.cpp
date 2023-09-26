//
// Created by Andrea Lipperi on 22/03/23.
//

#include "ProductListPage.h"


const long ProductListPage::IdButtonFav =::wxNewId();
const long ProductListPage::IdButtonCart =::wxNewId();
const long ProductListPage::IdButtonInsert =::wxNewId();
const long ProductListPage::IdButtonBack =::wxNewId();



BEGIN_EVENT_TABLE (ProductListPage, wxFrame)
                EVT_BUTTON(IdButtonFav, ProductListPage::IsFavourites)
                EVT_BUTTON(IdButtonCart, ProductListPage::IsCart)
                EVT_BUTTON(IdButtonInsert, ProductListPage::IsInsert)
                EVT_BUTTON(IdButtonBack, ProductListPage::ComeBack)

END_EVENT_TABLE()

ProductListPage::ProductListPage(Engine *e, const wxString &title, std::string sub, std::string disp): engine(e), sub_name(std::move(sub)), disponibility(std::move(disp)),
       wxFrame(nullptr, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {


    client = engine->get_client();
    username = client->get_username();

    db_store = engine->get_db_store();
    db_fav = engine->get_db_fav();
    db_cart = engine->get_db_cart();
    fav = make_shared<Favourites>(username);
    cart = make_shared<Cart>(username);

    prod_list = db_store->select_for_client(sub_name, disponibility);

    if (prod_list.empty()) {
        wxMessageBox("There aren't products with these characteristics", "Error", wxICON_ERROR);
        Close();
    } else {


        int row = db_store->select_count_for_client(sub_name, disponibility);


        grid = new wxGrid(this, wxID_ANY);
        grid->CreateGrid(row, 4);
        grid->SetColLabelValue(0, "Name Product");
        grid->SetColLabelValue(1, "Price");
        grid->SetColLabelValue(2, "Provider Name");
        grid->SetColLabelValue(3, "Disponibility");



        for (int i = 0; i < row; i++) {
            string name_prod = prod_list[i]->get_desc();
            float p = prod_list[i]->get_price();
            string price(to_string(p));
            string name_prov = prod_list[i]->get_username_prov();
            int a_q = prod_list[i]->get_q_available();
            string available_q(to_string(a_q));

            grid->SetReadOnly(i, 0, true);
            grid->SetCellValue(i, 0, name_prod);
            grid->SetReadOnly(i, 1, true);
            grid->SetCellValue(i, 1, price);
            grid->SetReadOnly(i, 2, true);
            grid->SetCellValue(i, 2, name_prov);
            grid->SetReadOnly(i, 3, true);
            grid->SetCellValue(i, 3, available_q);

        }
        grid->SetSelectionMode(wxGrid::wxGridSelectRows);
        grid->AutoSize();


        FavButton = new wxButton(this, IdButtonFav, _T ("Add to favourites"), wxDefaultPosition, wxDefaultSize, 0);
        CartButton = new wxButton(this, IdButtonCart, _T ("Add to cart"), wxDefaultPosition, wxDefaultSize, 0);
        Back = new wxButton(this, IdButtonBack, _T ("Back"), wxDefaultPosition, wxDefaultSize, 0);

        sizer = new wxBoxSizer(wxVERTICAL);


        sizer->Add(grid, 1, wxEXPAND , 5);
        sizer->Add(FavButton, 1, wxEXPAND, 5);
        sizer->Add(CartButton, 1, wxEXPAND , 5);
        sizer->Add(Back, 1, wxALL, 5);

        SetSizer(sizer);

        Centre();

    }
}


void ProductListPage::IsFavourites(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }

        if (db_fav->control_if_exist(prod_list[row])) {
            wxMessageBox("Product already in your favourites list", "Error", wxICON_ERROR);
        } else {
            wxMessageBox("Insert gone well", "", wxICON_ERROR);
            client->add_to_fav(prod_list[row]);
            db_fav->add_to_db();
        }

    }
}

void ProductListPage::IsCart(wxCommandEvent &event)  {
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        sizer->Hide(FavButton);
        sizer->Hide(CartButton);
        auto *q = new wxStaticText(this, -1, wxT("Insert Quantity"));
        sizer->Add(q, 0,  wxALL, 5);
        spinCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);
        sizer->Add(spinCtrl, 0,  wxALL, 5);
        InsertButton=new wxButton(this,IdButtonInsert,_T ("Insert"),wxDefaultPosition,wxDefaultSize,0);
        sizer->Add(InsertButton, 0,  wxALL, 5);
        wxSize currentSize = GetSize();
        int newWidth = currentSize.GetWidth() +1;
        int newHeight = currentSize.GetHeight() +1;
        SetSize(newWidth, newHeight);
    }
}

void ProductListPage::IsInsert(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        if (spinCtrl->GetValue() < 1) {
            wxMessageBox("Insert a valid quantity", "Error", wxICON_ERROR);
        } else {
            wxArrayInt selectedRows = grid->GetSelectedRows();
            int row;
            for (size_t i = 0; i < selectedRows.GetCount(); i++) {
                row = selectedRows[i];
            }

            bool ctrl = db_cart->control_if_exist(prod_list[row]);
            int quantity = spinCtrl->GetValue();
            if (quantity <= prod_list[row]->get_q_available()) {
                if (ctrl) {
                    if (control == 0) {
                        wxMessageBox("Product already in cart, click againg in insert if you want to add this quantity",
                                     "Error", wxICON_ERROR);
                    } else {
                        int i = 0;
                        int count = 0;
                        cart=client->get_cart();
                        prod_l = cart->get_products();
                        while (i< prod_l.size() && count == 0) {
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
                        int id_cart = db_cart->select_id_cart(prod_l[i]->get_desc(), prod_l[i]->get_username_prov());
                        int control_q = new_quantity + prod_l[i]->get_quantity();
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
                    wxMessageBox("Insert gone well", "", wxICON_ERROR);
                    prod_list[row]->set_quantity(quantity);
                    client->add_to_cart(prod_list[row]);
                    db_cart->add_to_db();
                }
            }
        }
    }
}

void ProductListPage::ComeBack(wxCommandEvent &event) {
    Close();
}
