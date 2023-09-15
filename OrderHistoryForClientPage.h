//
// Created by Andrea Lipperi on 04/05/23.
//

#ifndef INGROSSO_ONLINE_ORDERHISTORYFORCLIENTPAGE_H
#define INGROSSO_ONLINE_ORDERHISTORYFORCLIENTPAGE_H

#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/grid.h"
#include "OrdersList.h"
#include "Engine.h"
#include "User.h"
#include "dbOrdersManager.h"
#include "OrdersList.h"
#include "Order.h"
#include "Date.h"

class OrderHistoryForClientPage : public wxDialog{
public:
    OrderHistoryForClientPage(Engine *e, const wxString& title, int control);

    static const long IdButtonCancel;
    static const long IdButtonView;

    DECLARE_EVENT_TABLE()


private:
    void CancelOrder(wxCommandEvent& event);
    void ViewOrder(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);

    wxButton *Cancel;
    wxButton *View;
    wxTextCtrl *sub;
    wxTextCtrl *cat;
    wxTextCtrl *name;
    wxTextCtrl *cost;
    wxBoxSizer *sizer;
    wxSpinCtrl* spinCtrl;
    wxGrid *grid;
    std::string username;
    wxChoice* choiceOrder;
    int ctrl;
    Engine *engine;
    shared_ptr<User> user;
    std::vector<shared_ptr<Order>> order;
    shared_ptr<dbOrdersManager> db_order;
    shared_ptr <OrdersList> orders_list;
};


#endif //INGROSSO_ONLINE_ORDERHISTORYFORCLIENTPAGE_H
