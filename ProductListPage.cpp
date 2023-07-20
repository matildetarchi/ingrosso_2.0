//
// Created by Andrea Lipperi on 22/03/23.
//

#include "ProductListPage.h"
#include "SelectionSubcategoryPage.h"
#include "GlobalVariables.h"
#include "favourite.h"
#include "Cart.h"
#include <wx/grid.h>
#include <wx/app.h>
#include <wx/spinctrl.h>

const long ProductListPage::IdButtonFav =::wxNewId();
const long ProductListPage::IdButtonCart =::wxNewId();
const long ProductListPage::IdButtonInsert =::wxNewId();

BEGIN_EVENT_TABLE (ProductListPage, wxFrame)
                EVT_BUTTON(IdButtonFav, ProductListPage::IsFavourites)
                EVT_BUTTON(IdButtonCart, ProductListPage::IsCart)
                EVT_BUTTON(IdButtonInsert, ProductListPage::IsInsert)
END_EVENT_TABLE()

ProductListPage::ProductListPage(const wxString &title, const std::string &sub, const std::string &disp):
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {
    sub_name=sub;
    disponibility=disp;
    username=GlobalVariables::GetInstance().GetValueUsername();

    wxStaticText *order = new wxStaticText(this, -1, wxT("OrderProduct By"));
    wxString myString[]={"Name Product", "Price", "Provider Name"};
    choiceOrder=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceOrder->Append("Select");
    choiceOrder->Append(3,myString);
    choiceOrder->Bind(wxEVT_CHOICE, &ProductListPage::OnChoice, this);


    StoreProduct store;
    int row = store.select_count_for_client(sub, disponibility);

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 4);
    grid->SetColLabelValue(0, "Name Product");
    grid->SetColLabelValue(1, "Price");
    grid->SetColLabelValue(2, "Provider Name");
    grid->SetColLabelValue(3, "Disponibility");
    mat_store=store.select_for_client(sub_name,disponibility);

    for (int i = 0; i < store.select_count_for_client(sub_name, disponibility); i++) {

        for (int col = 0; col < 4; col++) {
                grid->SetReadOnly(i, col, true);
                grid->SetCellValue(i, col,  mat_store[i][col]);
        }
    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();


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
    StoreProduct store;
    string order=event.GetString().ToStdString();
    mat_store=store.select_for_client(sub_name, disponibility,order);
    for (int i = 0; i < store.select_count_for_client(sub_name, disponibility); i++) {
        for (int col = 0; col < 4; col++) {
            grid->SetReadOnly(i, col, true);
            grid->SetCellValue(i, col,  mat_store[i][col]);
        }

    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();
}
void ProductListPage::IsFavourites(wxCommandEvent &event) {
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        int id_product = stoi(mat_store[row][4]);
        FavouriteProduct *fav = new FavouriteProduct(id_product, username, mat_store[row][2]);
        fav->add();
    }
}

void ProductListPage::IsCart(wxCommandEvent &event)  {
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        sizer->Hide(FavButton);
        sizer->Hide(CartButton);
        wxStaticText *q = new wxStaticText(this, -1, wxT("Insert Quantity"));
        sizer->Add(q, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
        spinCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);
        sizer->Add(spinCtrl, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
        wxButton *insert=new wxButton(this,IdButtonInsert,_T ("Add to cart"),wxDefaultPosition,wxDefaultSize,0);
        sizer->Add(insert, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
        wxSize currentSize = GetSize();
        int newWidth = currentSize.GetWidth() +1;
        int newHeight = currentSize.GetHeight() +1;
        SetSize(newWidth, newHeight);
    }
}
void ProductListPage::IsInsert(wxCommandEvent &event) {
    if (spinCtrl->GetValue()<1){
        wxMessageBox("Insert a valid quantity", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        std::string username_cust=GlobalVariables::GetInstance().GetValueUsername();
        int quantity = spinCtrl->GetValue();
        int cod_product = stoi(mat_store[row][4]);
        CartProduct *cart = new CartProduct(quantity,cod_product, username_cust, mat_store[row][2]);
        cart->add();
    }
}
