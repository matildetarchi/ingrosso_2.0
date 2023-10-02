//
// Created by Andrea Lipperi on 08/05/23.
//

#include "UsersDataListPage.h"


const long UsersDataListPage::IdButtonBack =::wxNewId();

BEGIN_EVENT_TABLE (UsersDataListPage, wxFrame)
                EVT_BUTTON(IdButtonBack, UsersDataListPage::ComeBack)
END_EVENT_TABLE()

UsersDataListPage::UsersDataListPage(Engine *e, const wxString &title, const std::string &var_city): engine(e),
                   wxFrame(nullptr, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {

    user = engine->get_user();
    db_user = engine->get_db_user();
    city = var_city;
    type = user->get_type();


    int row = db_user->select_count_users(type,city);

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 5);
    grid->SetColLabelValue(0, "Business Name");
    grid->SetColLabelValue(1, "Username");
    grid->SetColLabelValue(2, "Email");
    grid->SetColLabelValue(3, "Address");
    grid->SetColLabelValue(4, "City");

    if (row >0) {
        user_list = db_user->select_users(type, city);

        for (int i = 0; i < row; i++) {

            string b_n = user_list[i]->get_bus_name();
            string us = user_list[i]->get_username();
            string email = user_list[i]->get_email();
            string address = user_list[i]->get_address();
            string user_city = user_list[i]->get_city();

            grid->SetReadOnly(i, 0, true);
            grid->SetCellValue(i, 0, b_n);
            grid->SetReadOnly(i, 1, true);
            grid->SetCellValue(i, 1, us);
            grid->SetReadOnly(i, 2, true);
            grid->SetCellValue(i, 2, email);
            grid->SetReadOnly(i, 3, true);
            grid->SetCellValue(i, 3, address);
            grid->SetReadOnly(i, 4, true);
            grid->SetCellValue(i, 4, user_city);
        }
    }
    grid->AutoSize();


    Back = new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(grid, 1, wxALL, 5);
    sizer->Add(Back, 1, wxALL, 5);
    SetSizer(sizer);

    Centre();
}

void UsersDataListPage::ComeBack(wxCommandEvent &event) {
    Close();
}