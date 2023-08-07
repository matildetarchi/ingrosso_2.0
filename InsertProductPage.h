//
// Created by dario on 05/12/2022.
//
/*
#ifndef INGROSSO_ONLINE_INSERTPRODUCTPAGE_H
#define INGROSSO_ONLINE_INSERTPRODUCTPAGE_H

#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/string.h"
#include "wx/grid.h"
#include <wx/spinctrl.h>
#include <string>
#include "HomePageProviders.h"
#include "dbCategoriesManager.h"

class InsertProductPage: public wxFrame {
public:
    InsertProductPage(const wxString &title);

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
};

#endif //INGROSSO_ONLINE_INSERTPRODUCTPAGE_H
 */