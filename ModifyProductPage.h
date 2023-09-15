//
// Created by Andrea Lipperi on 02/05/23.
//
#ifndef INGROSSO_ONLINE_MODIFYPRODUCTPAGE_H
#define INGROSSO_ONLINE_MODIFYPRODUCTPAGE_H


#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/string.h"
#include <wx/spinctrl.h>
#include <string>
#include "HomePageProviders.h"
#include "store.h"
#include "Engine.h"
#include "dbStoreManager.h"
#include "Product.h"


class ModifyProductPage : public wxDialog{
public:
    ModifyProductPage(Engine *e, const wxString& title, int id_store);

    static const long IdButtonConfirm;
DECLARE_EVENT_TABLE()


private:
    void OnConfirm(wxCommandEvent& event);
    wxButton *Confirm;
    std::string username;
    int id;
    wxBoxSizer *sizer;
    std::string type;
    shared_ptr<Product> prod;
    wxTextCtrl *tcD;
    wxSpinCtrlDouble *tcP;
    wxSpinCtrl *tcQ;
    Engine* engine;
    shared_ptr<dbStoreManager> db_store;
    shared_ptr <Provider> prov;

};

#endif //INGROSSO_ONLINE_MODIFYPRODUCTPAGE_H
