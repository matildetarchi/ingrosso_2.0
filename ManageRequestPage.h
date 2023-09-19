//
// Created by Andrea Lipperi on 21/04/23.
//

#ifndef INGROSSO_ONLINE_MANAGEREQUESTPAGE_H
#define INGROSSO_ONLINE_MANAGEREQUESTPAGE_H


#include "Engine.h"
#include "SingleOrderProviderPage.h"
#include <ctime>


class ManageRequestPage: public wxDialog{
public:
    ManageRequestPage(Engine* e,const wxString& title, int control);

    static const long IdButtonConfirm;
    static const long IdButtonDeny;
    static const long IdButtonView;

DECLARE_EVENT_TABLE()


private:
    void OnConfirm(wxCommandEvent& event);
    void OnDeny(wxCommandEvent& event);
    void ViewOrder(wxCommandEvent& event);
    //void OnChoice(wxCommandEvent& event);

    wxButton *Confirm;
    wxButton *Deny;
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
    std::vector<shared_ptr<Order>> order;
    int ctrl;
    Engine* engine;
    shared_ptr<Provider> prov;
    shared_ptr<dbOrdersManager> db_order;
    shared_ptr <OrdersList> orders_list;
};




#endif //INGROSSO_ONLINE_MANAGEREQUESTPAGE_H
