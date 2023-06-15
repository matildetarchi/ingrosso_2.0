//
// Created by Andrea Lipperi on 20/04/23.
//

#ifndef INGROSSO_ONLINE_CARTPAGE_H
#define INGROSSO_ONLINE_CARTPAGE_H

#include "wx/wxhtml.h"
#include "wx/wx.h"
#include <string>
#include "user.h"
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

class CartPage : public wxFrame {
public:
    CartPage(const wxString &title);
    static const long IdButtonRemove;
    static const long IdButtonOrder;
    static const long IdButtonHelp;
    static const long IdButtonComeBack;
DECLARE_EVENT_TABLE()


private:
    void IsRemove(wxCommandEvent &event);
    void IsOrder(wxCommandEvent &event);
    void IsHelp(wxCommandEvent &event);
    void ComeBack(wxCommandEvent& event);
    wxButton *Remove;
    wxBoxSizer *sizer;
    wxButton *Order;
    wxButton *Help;
    wxButton *Back;
    wxTextCtrl *sub;
    wxTextCtrl *cat;
    wxTextCtrl *name;
    wxTextCtrl *cost;
    std::string username;
    std::vector<std::vector<std::string>> mat_cart;
    wxGrid *grid;
    wxSpinCtrl* spinCtrl;
};
#endif //INGROSSO_ONLINE_CARTPAGE_H
