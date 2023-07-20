//
// Created by dario on 20/04/2023.
//

#include "SingleOrderProviderPage.h"
#include "GlobalVariables.h"

const long SingleOrderProviderPage::IdButtonBack =::wxNewId();


BEGIN_EVENT_TABLE (SingleOrderProviderPage, wxDialog)
                EVT_BUTTON(IdButtonBack, SingleOrderProviderPage::ComeBack)


END_EVENT_TABLE()

SingleOrderProviderPage::SingleOrderProviderPage(const wxString &title, const std::string &code_order):
        wxDialog(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {
    order=code_order;
    username=GlobalVariables::GetInstance().GetValueUsername();

    Orders orders;
    int row = orders.select_count_single_order_for_provider(username, order);

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 4);
    grid->SetColLabelValue(0, "Quantity Requested");
    grid->SetColLabelValue(1, "Total Price");
    grid->SetColLabelValue(2, "Product");
    grid->SetColLabelValue(3, "Quantity Available In Store");

    mat_order = orders.select_single_order_for_provider(username, order);

    for (int i = 0; i < orders.select_count_single_order_for_provider(username, order); i++) {

        for (int col = 0; col < 4; col++) {
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

void SingleOrderProviderPage::ComeBack(wxCommandEvent &event) {

    Close();

}