//
// Created by Andrea Lipperi on 20/04/23.
//

#include "CartPage.h"




const long CartPage::IdButtonRemove =::wxNewId();
const long CartPage::IdButtonOrder =::wxNewId();
const long CartPage::IdButtonHelp =::wxNewId();
const long CartPage::IdButtonComeBack =::wxNewId();

BEGIN_EVENT_TABLE (CartPage, wxFrame)
                EVT_BUTTON(IdButtonRemove, CartPage::IsRemove)
                EVT_BUTTON(IdButtonOrder, CartPage::IsOrder)
                EVT_BUTTON(IdButtonHelp, CartPage::IsHelp)
                EVT_BUTTON(IdButtonComeBack, CartPage::ComeBack)
END_EVENT_TABLE()

CartPage::CartPage(Engine *e, const wxString &title): engine(e),
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {


    user = engine->get_user();
    username = user->get_username();
    db_cart = engine->get_db_cart();
    db_ord = engine->get_db_order();

    db_cart->select();
    int num_prod = db_cart->select_count_of_prod();
    cart = user->get_cart();
    prod_list = cart->get_products();


    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(num_prod, 4);
    grid->SetColLabelValue(0, "Name Product");
    grid->SetColLabelValue(1, "Price");
    grid->SetColLabelValue(2, "Provider Name");
    grid->SetColLabelValue(3, "Quantity to Order");



       for (int i = 0; i < num_prod; i++) {

           string name_prod = prod_list[i]->get_desc();
           int p = prod_list[i]->get_price();
           string price(to_string(p));
           string name_prov = prod_list[i]->get_username_prov();
           int q= prod_list[i]->get_quantity();
           string quantity(to_string(q));

           grid->SetReadOnly(i, 0, true);
           grid->SetCellValue(i, 0, name_prod);
           grid->SetReadOnly(i, 1, true);
           grid->SetCellValue(i, 1, price);
           grid->SetReadOnly(i, 2, true);
           grid->SetCellValue(i, 2, name_prov);
           grid->SetColFormatNumber(3);
           grid->SetCellValue(i, 3,  quantity);
    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();

    Remove=new wxButton(this,IdButtonRemove,_T ("Remove"),wxDefaultPosition,wxDefaultSize,0);
    Order=new wxButton(this,IdButtonOrder,_T ("Do OrderProduct"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton(this,IdButtonComeBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);
    Help=new wxButton(this,IdButtonHelp,_T ("?"),wxDefaultPosition,wxDefaultSize,0);


    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(Help, 0, wxEXPAND | wxALL, 3);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Remove, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Order, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Back, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);


    Centre();


}

void CartPage::IsRemove(wxCommandEvent &event) {
    if (grid->GetSelectedRows().IsEmpty()) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }

        int id = prod_list[row]->get_id_store();
        db_cart->remove_prod(id);
        grid->DeleteRows(row);
    }
}

void CartPage::IsOrder(wxCommandEvent &event) {

    int row = db_cart->select_count_of_prod();

    int i=0;
    while (i<row){
        int new_quantity= stoi(grid->GetCellValue(i,3).ToStdString());
        prod_list[i]->set_quantity(new_quantity);
        i++;
    }
    db_ord->add_to_db();
    db_cart->remove_all();
    grid->ClearGrid();
}

void CartPage::ComeBack(wxCommandEvent &event) {
    Close();
}


void CartPage::IsHelp(wxCommandEvent &event) {
    wxMessageBox("You can change the quantity to order directly in the grid", "Help", wxICON_ERROR);
}
