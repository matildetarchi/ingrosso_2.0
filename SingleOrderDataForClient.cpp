//
// Created by Andrea Lipperi on 04/05/23.
//

#include "SingleOrderDataForClient.h"
#include "orderProduct.h"
#include "GlobalVariables.h"

const long SingleOrderDataForClient::IdButtonBack =::wxNewId();


BEGIN_EVENT_TABLE (SingleOrderDataForClient, wxDialog)
                EVT_BUTTON(IdButtonBack, SingleOrderDataForClient::ComeBack)


END_EVENT_TABLE()

SingleOrderDataForClient::SingleOrderDataForClient(const wxString &title, const std::string &code_order, const std::string &us_prov):
        wxDialog(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {
    order=code_order;
    prov=us_prov;
    username=GlobalVariables::GetInstance().GetValueUsername();

    OrderProduct orders;
    int row = orders.select_count_single_order_for_client(username, order, prov);

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 3);
    grid->SetColLabelValue(0, "Quantity Requested");
    grid->SetColLabelValue(1, "Total Price");
    grid->SetColLabelValue(2, "Product");

    mat_order = orders.select_single_order_for_client(username, order, prov);

    for (int i = 0; i < orders.select_count_single_order_for_client(username, order, prov); i++) {

        for (int col = 0; col < 3; col++) {
            grid->SetReadOnly(i, col, true);
            grid->SetCellValue(i, col, mat_order[i][col]);
        }
    }
    grid->AutoSize();


    Back = new wxButton(this, IdButtonBack, _T ("Back"), wxDefaultPosition, wxDefaultSize, 0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);

    sizer->Add(Back, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();
}

void SingleOrderDataForClient::ComeBack(wxCommandEvent &event) {

    Close();

}