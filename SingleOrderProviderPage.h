//
// Created by Andrea Lipperi on 26/04/23.
//

#ifndef INGROSSO_ONLINE_SINGLEORDERPROVIDERPAGE_H
#define INGROSSO_ONLINE_SINGLEORDERPROVIDERPAGE_H

#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/grid.h"
#include <fstream>
#include "Engine.h"


class SingleOrderProviderPage: public wxDialog {
public:
    SingleOrderProviderPage(Engine *e, const wxString& title, int code_order);

    static const long IdButtonBack;

DECLARE_EVENT_TABLE()


private:
    void ComeBack(wxCommandEvent& event);

    wxButton *Back;
    wxTextCtrl *sub;
    wxTextCtrl *disp;
    wxTextCtrl *cat;
    wxTextCtrl *name;
    wxTextCtrl *cost;
    wxBoxSizer *sizer;
    wxSpinCtrl* spinCtrl;
    wxGrid *grid;
    int id_order;
    std::string username;
    shared_ptr<Provider> prov;
    Engine *engine;
    shared_ptr <OrdersList> orders_list;
    std::vector<shared_ptr<Order>> orders;
    shared_ptr<Order> order;
    std::vector<shared_ptr<Product>> order_p;

};


#endif //INGROSSO_ONLINE_SINGLEORDERPROVIDERPAGE_H
