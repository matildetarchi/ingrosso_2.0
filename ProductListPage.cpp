//
// Created by Andrea Lipperi on 22/03/23.
//

#include "ProductListPage.h"


const long ProductListPage::IdButtonFav =::wxNewId();
const long ProductListPage::IdButtonCart =::wxNewId();


BEGIN_EVENT_TABLE (ProductListPage, wxFrame)
                EVT_BUTTON(IdButtonFav, ProductListPage::IsFavourites)
                EVT_BUTTON(IdButtonCart, ProductListPage::IsCart)
END_EVENT_TABLE()

ProductListPage::ProductListPage(Engine *e, const wxString &title, std::string sub, std::string disp): engine(e), sub_name(std::move(sub)), disponibility(std::move(disp)), wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {


    client = engine->get_client();
    username = client->get_username();

    db_store = engine->get_db_store();
    db_fav = engine->get_db_fav();
    db_cart = engine->get_db_cart();
    fav = make_shared<Favourites>(username);
    cart = make_shared<Cart>(username);

    wxStaticText *order = new wxStaticText(this, -1, wxT("Order By"));
    wxString myString[]={"Name Product", "Price", "Provider Name"};
    choiceOrder=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceOrder->Append("Select");
    choiceOrder->Append(3,myString);
    choiceOrder->Bind(wxEVT_CHOICE, &ProductListPage::OnChoice, this);




    FavButton=new wxButton (this,IdButtonFav,_T ("Add to favourites"),wxDefaultPosition,wxDefaultSize,0);
    CartButton=new wxButton (this,IdButtonCart,_T ("Add to cart"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(order, 0, wxALL, 5);
    sizer->Add(choiceOrder, 0, wxALL, 5);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    sizer->Add(FavButton, 1, wxEXPAND | wxALL, 5);
    sizer->Add(CartButton, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();


}
void ProductListPage::OnChoice(wxCommandEvent& event) {

    string order = event.GetString().ToStdString();
    prod_list = db_store->select_for_client(sub_name, disponibility, order);
    int row = db_store->select_count_for_client(sub_name, disponibility);




    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 4);
    grid->SetColLabelValue(0, "Name Product");
    grid->SetColLabelValue(1, "Price");
    grid->SetColLabelValue(2, "Provider Name");
    grid->SetColLabelValue(3, "Disponibility");


    for (int i = 0; i < row; i++) {
        string name_prod = prod_list[i]->get_desc();
        int p = prod_list[i]->get_price();
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

        grid->SetSelectionMode(wxGrid::wxGridSelectRows);
        grid->AutoSize();
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
        client->add_to_fav(prod_list[row]);
        db_fav->add_to_db();

    }
    Close();
}

void ProductListPage::IsCart(wxCommandEvent &event)  {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        if (spinCtrl->GetValue()<1){
            wxMessageBox("Insert a valid quantity", "Error", wxICON_ERROR);
        } else {
            wxArrayInt selectedRows = grid->GetSelectedRows();
            int row;
            for (size_t i = 0; i < selectedRows.GetCount(); i++) {
                row = selectedRows[i];
            }

            int quantity = spinCtrl->GetValue();
            prod_list[row]->set_quantity(quantity);

            client->add_to_cart(prod_list[row]);
            db_cart->add_to_db();
        }

    }
    Close();
}


