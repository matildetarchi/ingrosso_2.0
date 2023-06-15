//
// Created by Andrea Lipperi on 03/04/23.
//

#include "FavouritesListPage.h"
#include "GlobalVariables.h"
#include "orderProduct.h"
#include "favourite.h"
#include "wx/grid.h"

#include <wx/spinctrl.h>

const long FavouritesListPage::IdButtonRemove =::wxNewId();
const long FavouritesListPage::IdButtonOrder =::wxNewId();
const long FavouritesListPage::IdButtonComeBack =::wxNewId();

BEGIN_EVENT_TABLE (FavouritesListPage, wxFrame)
                EVT_BUTTON(IdButtonRemove, FavouritesListPage::IsRemove)
                EVT_BUTTON(IdButtonOrder, FavouritesListPage::IsOrder)
                EVT_BUTTON(IdButtonComeBack, FavouritesListPage::ComeBack)
END_EVENT_TABLE()

FavouritesListPage::FavouritesListPage(const wxString &title):
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {

    username=GlobalVariables::GetInstance().GetValueUsername();
    FavouriteProduct fav;
    int row = fav.select_count(username);
    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 4);
    grid->SetColLabelValue(0, "Name Product");
    grid->SetColLabelValue(1, "Price");
    grid->SetColLabelValue(2, "Provider Name");
    grid->SetColLabelValue(3, "Quantity to Order");

    mat_fav=fav.select(username);

    for (int i = 0; i < fav.select_count(username); i++) {

        for (int col = 0; col < 3; col++) {
            grid->SetReadOnly(i, col, true);
            grid->SetCellValue(i, col,  mat_fav[i][col]);
        }
        grid->SetColFormatNumber(3);
        grid->SetCellValue(i, 3, "0");
    }
    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();

    Remove=new wxButton(this,IdButtonRemove,_T ("Remove"),wxDefaultPosition,wxDefaultSize,0);
    Order=new wxButton(this,IdButtonOrder,_T ("Do Order"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton(this,IdButtonComeBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);


    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Remove, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Order, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Back, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);


    Centre();


}

void FavouritesListPage::IsRemove(wxCommandEvent &event) {
    if (grid->GetSelectedRows() == 0) {
        wxMessageBox("Choose a product", "Error", wxICON_ERROR);
    } else {
        wxArrayInt selectedRows = grid->GetSelectedRows();
        int row;
        for (size_t i = 0; i < selectedRows.GetCount(); i++) {
            row = selectedRows[i];
        }
        FavouriteProduct table;
        int id = stoi(mat_fav[row][4]);
        table.remove_prod(id);
        grid->DeleteRows(row);
    }
}

void FavouritesListPage::IsOrder(wxCommandEvent &event) {
    FavouriteProduct fav;
    int row = fav.select_count(username);
    int k=0;
    int control=1;
    string quantity;
    while (k<row && control==1) {
        quantity = grid->GetCellValue(k, 3).ToStdString();
        if (stoi(quantity) == 0) {
            control=0;
        }
        k++;
    }
    if (control==1) {
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
            id_order[j]=ord.select_id_last_order(mat_fav[j][2])+1;
            j++;
        }
        while (i<row){
            quantity = grid->GetCellValue(i, 3).ToStdString();
            OrderProduct *order = new OrderProduct(stoi(quantity),stoi(mat_fav[i][3]), "S",data,username,mat_fav[i][2],id_order[i]);
            order->add();
            i++;
        }
    } else {
        wxMessageBox("Insert a valid quantity value in every row", "Error", wxICON_ERROR);
    }
}

void FavouritesListPage::ComeBack(wxCommandEvent &event) {
    Close();
}
