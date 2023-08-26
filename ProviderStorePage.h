//
// Created by Andrea Lipperi on 02/05/23.
//
/*
#ifndef INGROSSO_ONLINE_PROVIDERSTOREPAGE_H
#define INGROSSO_ONLINE_PROVIDERSTOREPAGE_H
#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/grid.h"
#include "Store.h"
#include "ModifyProductPage.h"
#include "Engine.h"
#include "User.h"
#include "dbStoreManager.h"
#include "Product.h"

class ProviderStorePage: public wxDialog{
public:
    ProviderStorePage(Engine *e, const wxString& title);

    static const long IdButtonDelete;
    static const long IdButtonBack;
    static const long IdButtonModify;

DECLARE_EVENT_TABLE()


private:
    void DeleteProduct(wxCommandEvent& event);
    void ComeBack(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    void ModifyProduct(wxCommandEvent& event);

    wxButton *Delete;
    wxButton *Modify;
    wxButton *Back;
    wxBoxSizer *sizer;
    wxGrid *grid;
    std::string username;
    wxChoice* choiceOrder;
    Engine *engine;
    shared_ptr<User> user;
    dbStoreManager *db_store;
    vector<shared_ptr<Product>> prod_list;
    shared_ptr<Store> store;

};

#endif //INGROSSO_ONLINE_PROVIDERSTOREPAGE_H
*/