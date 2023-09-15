//
// Created by dario on 05/12/2022.
//

#ifndef INGROSSO_ONLINE_INSERTPRODUCTPAGE_H
#define INGROSSO_ONLINE_INSERTPRODUCTPAGE_H

#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/string.h"
#include "wx/grid.h"
#include <string>
#include "dbSubcategoriesManager.h"
#include "dbCategoriesManager.h"
#include "store.h"
#include <vector>
#include <wx/spinctrl.h>
#include "Engine.h"
#include "dbStoreManager.h"
#include "Provider.h"

class InsertProductPage: public wxFrame {
public:
    InsertProductPage(Engine *e, const wxString &title);

    static const long IdButtonInsert;
    static const long IdButtonComeBack;


DECLARE_EVENT_TABLE()
private:
    void ComeBack(wxCommandEvent& event);
    void InsertProduct(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    wxButton *Insert;
    wxButton *Back;
    wxTextCtrl *tcCategory;
    wxTextCtrl *tcName;
    wxBoxSizer *sizer;
    wxTextCtrl *tcCost;
    wxChoice* choiceC;
    wxChoice* choiceSubC;
    wxSpinCtrl* tcQ;
    wxSpinCtrlDouble *tcC;
    Engine *engine;
    shared_ptr<dbCategoriesManager> db_categories;
    shared_ptr<dbSubcategoriesManager> db_subcategories;
    shared_ptr<Provider> prov;
    shared_ptr<Store> store;
    shared_ptr<dbStoreManager> db_store;

};

#endif //INGROSSO_ONLINE_INSERTPRODUCTPAGE_H
