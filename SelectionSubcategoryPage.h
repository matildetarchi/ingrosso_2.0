//
// Created by dario on 12/11/2022.
//

#ifndef BUTTON_WXWIDGETS_FRAME_H
#define BUTTON_WXWIDGETS_FRAME_H

#include "wx/wxhtml.h"
#include "wx/wx.h"
#include "dbCategoriesManager.h"
#include "dbSubcategoriesManager.h"
#include "ProductListPage.h"
#include <string>
#include <vector>
#include "Engine.h"
#include <memory>


class SelectionSubcategoryPage: public wxFrame {
public:
    SelectionSubcategoryPage(Engine *e , const wxString &title);

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
    wxChoice* choiceC;
    wxChoice* choiceSubC;
    wxChoice* choiceDisp;
    Engine *engine;
    shared_ptr<dbSubcategoriesManager> db_subcat;
    shared_ptr<dbCategoriesManager> db_cat;
};
#endif //BUTTON_WXWIDGETS_FRAME_H
