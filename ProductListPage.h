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
#include "wx/grid.h"
#include "Engine.h"
#include "favourites.h"
#include "cart.h"
#include <wx/app.h>
#include <memory>
#include <wx/spinctrl.h>
#include "dbStoreManager.h"
#include "store.h"
#include "Product.h"
#include "dbFavouritesManager.h"
#include "dbCartManager.h"




class ProductListPage : public wxFrame {
public:
    ProductListPage(Engine *e, const wxString &title, std::string sub, std::string disp);
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
    Engine *engine;
    std::shared_ptr<User> user;
    std::shared_ptr<dbStoreManager> db_store;
    std::vector<shared_ptr<Product>> prod_list;
    std::shared_ptr<Store> store;
    std::shared_ptr<Favourites> fav;
    std::shared_ptr<dbFavouritesManager> db_fav;
    std::shared_ptr<Cart> cart;
    std::shared_ptr<dbCartManager> db_cart;
};

#endif //INGROSSO_ONLINE_PRODUCTLISTPAGE_H
