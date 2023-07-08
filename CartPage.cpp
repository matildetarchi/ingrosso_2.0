//
// Created by Andrea Lipperi on 20/04/23.
//

#include "CartPage.h"
#include "GlobalVariables.h"
#include "Cart.h"
#include "OrdersList.h"
#include "wx/grid.h"

#include <wx/spinctrl.h>

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

CartPage::CartPage(const wxString &title):
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {

    username=GlobalVariables::GetInstance().GetValueUsername();
    CartProduct cart;
    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(cart.select_count(username), 4);
    grid->SetColLabelValue(0, "Name Product");
    grid->SetColLabelValue(1, "Price");
    grid->SetColLabelValue(2, "Provider Name");
    grid->SetColLabelValue(3, "Quantity to OrderProduct");
    mat_cart=cart.select(username);
    for (int i = 0; i < cart.select_count(username); i++) {

        for (int col = 0; col < 3; col++) {
            grid->SetReadOnly(i, col, true);
            grid->SetCellValue(i, col,  mat_cart[i][col]);
        }
        grid->SetColFormatNumber(3);
        grid->SetCellValue(i, 3,  mat_cart[i][3]);
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
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        CartProduct *table;
        int id = stoi(mat_cart[row][5]);
        table->remove_prod(id);
        grid->DeleteRows(row);
    }
}

void CartPage::IsOrder(wxCommandEvent &event) {
    CartProduct *cart;
    int row = cart->select_count(username);
    std::time_t t = std::time(nullptr); // ottiene il numero di secondi trascorsi dal 1 gennaio 1970
    std::tm* now = std::localtime(&t); // converte in una struttura tm con informazioni sulla data e sull'ora attuali
    int year = now->tm_year + 1900; // anno attuale (tm_year contiene l'anno dal 1900)
    int month = now->tm_mon + 1; // mese attuale (tm_mon contiene il mese da 0 a 11)
    int day = now->tm_mday; // giorno attuale del mese
    string data = ""+to_string(day)+"/"+ to_string(month)+"/"+ to_string(year)+"";
    int i=0;
    int j=0;
    int id_order[row];
    while (j<row) {
        OrderProduct ord;
        id_order[j]=ord.select_id_last_order(mat_cart[j][2])+1;
        j++;
    }
    while (i<row){
        string new_quantity=grid->GetCellValue(i,3).ToStdString();
        OrderProduct *order = new OrderProduct(stoi(new_quantity), stoi(mat_cart[i][4]), "S", data, username, mat_cart[i][2], id_order[i]);
        order->add();
        i++;
    }
    cart->remove_all(username);
    grid->ClearGrid();
}

void CartPage::ComeBack(wxCommandEvent &event) {
    Close();
}


void CartPage::IsHelp(wxCommandEvent &event) {
    wxMessageBox("You can change the quantity to order directly in the grid", "Help", wxICON_ERROR);
}