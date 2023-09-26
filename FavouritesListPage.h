//
// Created by Andrea Lipperi on 03/04/23.
//

#ifndef INGROSSO_ONLINE_FAVOURITESLISTPAGE_H
#define INGROSSO_ONLINE_FAVOURITESLISTPAGE_H

#include "wx/wxhtml.h"
#include "wx/wx.h"
#include "wx/grid.h"
#include <wx/spinctrl.h>
#include "Engine.h"



class FavouritesListPage : public wxFrame {
public:
    FavouritesListPage(Engine *e, const wxString &title);
    static const long IdButtonRemove;
    static const long IdButtonCart;
    static const long IdButtonComeBack;
    static const long IdButtonInsert;
DECLARE_EVENT_TABLE()


private:
    void IsRemove(wxCommandEvent &event);
    void IsCart(wxCommandEvent &event);
    void ComeBack(wxCommandEvent& event);
    void IsInsert(wxCommandEvent& event);
    void OnClose();
    wxButton *Remove;
    wxBoxSizer *sizer;
    wxBoxSizer *sizer_vertical;
    wxButton *Cart_button;
    wxButton *Back;
    wxButton *Insert;
    wxTextCtrl *sub;
    wxTextCtrl *cat;
    wxTextCtrl *name;
    wxTextCtrl *cost;
    std::string username;
    wxGrid *grid;
    wxSpinCtrl* spinCtrl;
    Engine *engine;
    std::shared_ptr<Client> client;
    std::shared_ptr<dbFavouritesManager> db_fav;
    std::shared_ptr<Favourites> fav;
    std::vector<std::shared_ptr<Product>> prod_list;
    std::vector<std::shared_ptr<Product>> prod_l;
    std::shared_ptr<dbCartManager> db_cart;
    std::shared_ptr<Cart> cart;
    int quantity;
    int control;
    shared_ptr<Product> p;
};


#endif //INGROSSO_ONLINE_FAVOURITESLISTPAGE_H
