//
// Created by Andrea Lipperi on 04/05/23.
//

#ifndef INGROSSO_ONLINE_ORDERHISTORYFORCLIENTPAGE_H
#define INGROSSO_ONLINE_ORDERHISTORYFORCLIENTPAGE_H

#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/grid.h"
#include "Engine.h"
#include "Date.h"

class OrderHistoryForClientPage : public wxDialog{
public:
    OrderHistoryForClientPage(Engine *e, const wxString& title, int control);

    static const long IdButtonCancel;
    static const long IdButtonView;
    static const long IdButtonBack;

    DECLARE_EVENT_TABLE()


private:
    void CancelOrder(wxCommandEvent& event);
    void ViewOrder(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    void ComeBack(wxCommandEvent& event);

    wxButton *Cancel;
    wxButton *View;
    wxButton *Back;
    wxTextCtrl *sub;
    wxTextCtrl *cat;
    wxTextCtrl *name;
    wxTextCtrl *cost;
    wxBoxSizer *sizer;
    wxBoxSizer *sizer_vertical;
    wxSpinCtrl* spinCtrl;
    wxGrid *grid;
    std::string username;
    wxChoice* choiceOrder;
    int ctrl;
    Engine *engine;
    shared_ptr<Client> client;
    std::vector<shared_ptr<Order>> order;
    std::vector<shared_ptr<Order>> order_op;
    shared_ptr<dbOrdersManager> db_order;
    shared_ptr <OrdersList> orders_list;
};


#endif //INGROSSO_ONLINE_ORDERHISTORYFORCLIENTPAGE_H
