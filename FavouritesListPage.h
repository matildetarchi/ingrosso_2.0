//
// Created by Andrea Lipperi on 03/04/23.
//

#ifndef INGROSSO_ONLINE_FAVOURITESLISTPAGE_H
#define INGROSSO_ONLINE_FAVOURITESLISTPAGE_H

#include "wx/wxhtml.h"
#include "wx/wx.h"
#include <string>
#include "User.h"
#include <iostream>
#include <fstream>
#include "MyApp.h"
#include "InitialPage.h"
#include "Menu.h"
#include "LogInPage.h"
#include "HomePageProviders.h"
#include "RegistrationPage.h"
#include "HomePageClient.h"
#include "wx/grid.h"
#include "GlobalVariables.h"
#include "orders.h"
#include "favourites.h"
#include <wx/spinctrl.h>




class FavouritesListPage : public wxFrame {
public:
    FavouritesListPage(const wxString &title);
    static const long IdButtonRemove;
    static const long IdButtonOrder;
    static const long IdButtonComeBack;
DECLARE_EVENT_TABLE()


private:
    void IsRemove(wxCommandEvent &event);
    void IsOrder(wxCommandEvent &event);
    void ComeBack(wxCommandEvent& event);
    wxButton *Remove;
    wxBoxSizer *sizer;
    wxButton *Order;
    wxButton *Back;
    wxTextCtrl *sub;
    wxTextCtrl *cat;
    wxTextCtrl *name;
    wxTextCtrl *cost;
    std::string username;
    std::vector<std::vector<std::string>> mat_fav;
    wxGrid *grid;
    wxSpinCtrl* spinCtrl;

};


#endif //INGROSSO_ONLINE_FAVOURITESLISTPAGE_H
