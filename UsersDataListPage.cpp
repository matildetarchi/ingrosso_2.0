//
// Created by Andrea Lipperi on 08/05/23.
//

#include "UsersDataListPage.h"
#include "SelectionCityPage.h"
#include "GlobalVariables.h"
#include "favourite.h"
#include "User.h"
#include "Cart.h"
#include <wx/grid.h>
#include <wx/app.h>
#include <wx/spinctrl.h>

const long UsersDataListPage::IdButtonBack =::wxNewId();

BEGIN_EVENT_TABLE (UsersDataListPage, wxFrame)
                EVT_BUTTON(IdButtonBack, UsersDataListPage::ComeBack)
END_EVENT_TABLE()

UsersDataListPage::UsersDataListPage(const wxString &title, const std::string &var_city):
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {
    city=var_city;
    type=GlobalVariables::GetInstance().GetValueType();

    wxStaticText *order = new wxStaticText(this, -1, wxT("Order By"));
    choiceOrder = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    if (city=="All") {
        wxString myString[] = {"Business Name", "Username", "Email", "Address", "City"};
        choiceOrder->Append("Select");
        choiceOrder->Append(5, myString);
    } else {
        wxString myString[] = {"Business Name", "Username", "Email", "Address"};
        choiceOrder->Append("Select");
        choiceOrder->Append(4, myString);
    }

    choiceOrder->Bind(wxEVT_CHOICE, &UsersDataListPage::OnChoice, this);

    User users;
    int row = users.select_count_users(type,city);

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row, 5);
    grid->SetColLabelValue(0, "Business Name");
    grid->SetColLabelValue(1, "Username");
    grid->SetColLabelValue(2, "Email");
    grid->SetColLabelValue(3, "Address");
    grid->SetColLabelValue(4, "City");

    mat_users=users.select_data_all_users(type,city);

    for (int i = 0; i < users.select_count_users(type,city); i++) {

        for (int col = 0; col < 5; col++) {
            grid->SetReadOnly(i, col, true);
            grid->SetCellValue(i, col,  mat_users[i][col]);
        }
    }
    grid->AutoSize();


    Back=new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(order, 0, wxALL, 5);
    sizer->Add(choiceOrder, 0, wxALL, 5);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Back, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();


}
void UsersDataListPage::OnChoice(wxCommandEvent& event) {
    User users;
    string order=event.GetString().ToStdString();
    mat_users=users.select_data_all_users(type,city,order);
    for (int i = 0; i < users.select_count_users(type,city); i++) {

        for (int col = 0; col < 5; col++) {
            grid->SetReadOnly(i, col, true);
            grid->SetCellValue(i, col,  mat_users[i][col]);
        }
    }
    grid->AutoSize();
}
void UsersDataListPage::ComeBack(wxCommandEvent &event) {
   Close();
}
