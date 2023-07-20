//
// Created by Andrea Lipperi on 22/03/23.
//

#ifndef INGROSSO_ONLINE_PRODUCTLISTPAGE_H
#define INGROSSO_ONLINE_PRODUCTLISTPAGE_H
#include "wx/wxhtml.h"
#include "wx/wx.h"
#include <string>
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




class ProductListPage : public wxFrame {
public:
    ProductListPage(const wxString &title, const std::string &sub, const std::string &disp);
    static const long IdButtonFav;
    static const long IdButtonCart;
    static const long IdButtonInsert;
DECLARE_EVENT_TABLE()


private:
    void IsFavourites(wxCommandEvent &event);
    void IsCart(wxCommandEvent& event);
    void IsInsert(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    wxButton *FavButton;
    wxButton *CartButton;
    wxButton *InsertButton;
    wxTextCtrl *sub;
    wxTextCtrl *cat;
    wxTextCtrl *name;
    wxTextCtrl *cost;
    wxBoxSizer *sizer;
    wxSpinCtrl* spinCtrl;
    wxGrid *grid;
    std::string sub_name;
    std::string disponibility;
    std::string username;
    wxChoice* choiceOrder;
    wxChoice* choiceQuantity;
    std::vector<std::vector<std::string>> mat_store;
};

#endif //INGROSSO_ONLINE_PRODUCTLISTPAGE_H
