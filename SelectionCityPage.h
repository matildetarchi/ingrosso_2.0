//
// Created by Andrea Lipperi on 08/05/23.
//

#ifndef INGROSSO_ONLINE_SELECTIONCITYPAGE_H
#define INGROSSO_ONLINE_SELECTIONCITYPAGE_H


#include "dbCityManager.h"
#include "UsersDataListPage.h"

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
    shared_ptr<dbCityManager> db_table;
};

#endif //INGROSSO_ONLINE_SELECTIONCITYPAGE_H
