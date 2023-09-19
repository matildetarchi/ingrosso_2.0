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
DECLARE_EVENT_TABLE()


private:
    void IsRemove(wxCommandEvent &event);
    void IsCart(wxCommandEvent &event);
    void ComeBack(wxCommandEvent& event);
    wxButton *Remove;
    wxBoxSizer *sizer;
    wxButton *Cart_button;
    wxButton *Back;
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
    std::shared_ptr<dbCartManager> db_cart;
    std::shared_ptr<Cart> cart;
};


#endif //INGROSSO_ONLINE_FAVOURITESLISTPAGE_H
