//
// Created by Andrea Lipperi on 20/04/23.
//

#ifndef INGROSSO_ONLINE_CARTPAGE_H
#define INGROSSO_ONLINE_CARTPAGE_H

#include <wx/spinctrl.h>
#include "wx/wxhtml.h"
#include "wx/wx.h"
#include "wx/grid.h"
#include "Engine.h"



class CartPage : public wxFrame {
public:
    CartPage(Engine *e, const wxString &title);

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
    wxBoxSizer *sizer_vertical;
    wxButton *Order;
    wxButton *Help;
    wxButton *Back;
    wxTextCtrl *sub{};
    wxTextCtrl *cat{};
    wxTextCtrl *name{};
    wxTextCtrl *cost{};
    std::string username;
    Engine *engine;
    wxGrid *grid;
    wxSpinCtrl* spinCtrl{};
    std::shared_ptr<Client> client;
    std::shared_ptr<dbCartManager> db_cart;
    std::vector<std::shared_ptr<Product>> prod_list;
    std::shared_ptr<Cart> cart;
    std::shared_ptr<dbOrdersManager> db_ord;


};
#endif //INGROSSO_ONLINE_CARTPAGE_H
