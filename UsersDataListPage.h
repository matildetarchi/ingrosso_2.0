//
// Created by Andrea Lipperi on 08/05/23.
//

#ifndef INGROSSO_ONLINE_USERSDATALISTPAGE_H
#define INGROSSO_ONLINE_USERSDATALISTPAGE_H

#include "wx/wxhtml.h"
#include "wx/wx.h"
#include <string>
#include <vector>
#include "User.h"
#include <iostream>
#include <fstream>
#include "MyApp.h"
#include "InitialPage.h"
#include "SelectionSubcategoryPage.h"
#include "LogInPage.h"
#include "HomePageProviders.h"
#include "RegistrationPage.h"
#include "HomePageClient.h"
#include "wx/grid.h"
#include "SelectionCityPage.h"
#include "favourites.h"
#include "cart.h"
#include <wx/app.h>
#include <wx/spinctrl.h>
#include "Engine.h"

class UsersDataListPage : public wxFrame {
public:
    UsersDataListPage(Engine *e, const wxString &title, const std::string &var_city);
    static const long IdButtonBack;
    DECLARE_EVENT_TABLE()


private:
    void OnChoice(wxCommandEvent& event);
    void ComeBack(wxCommandEvent& event);
    wxButton *Back;
    wxBoxSizer *sizer;
    wxGrid *grid;
    std::string city;
    std::string type;
    std::string username;
    wxChoice* choiceOrder;
    vector<vector<string>> mat_users;
    Engine *engine;
    shared_ptr<User> user;
    dbUserManager *db_user;
};

#endif //INGROSSO_ONLINE_USERSDATALISTPAGE_H
