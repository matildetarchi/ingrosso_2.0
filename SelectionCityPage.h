//
// Created by Andrea Lipperi on 08/05/23.
//

#ifndef INGROSSO_ONLINE_SELECTIONCITYPAGE_H
#define INGROSSO_ONLINE_SELECTIONCITYPAGE_H

#include "wx/wxhtml.h"
#include "wx/wx.h"
#include "dbCityManager.h"
#include "UsersDataListPage.h"
#include "dbCategoriesManager.h"
#include "ProductListPage.h"
#include <string>
#include <vector>
#include "Engine.h"

class SelectionCityPage : public wxFrame {
public:
    SelectionCityPage(Engine *e, const wxString &title);

    static const long IdButtonInsert;
    static const long IdButtonComeBack;


DECLARE_EVENT_TABLE()
private:
    void ComeBack(wxCommandEvent& event);
    void InsertCity(wxCommandEvent& event);
    wxButton *Insert;
    wxButton *Back;
    wxChoice* choiceC;
    Engine *engine;
};

#endif //INGROSSO_ONLINE_SELECTIONCITYPAGE_H
