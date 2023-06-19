//
// Created by Andrea Lipperi on 02/05/23.
//

#ifndef INGROSSO_ONLINE_PROVIDERSTOREPAGE_H
#define INGROSSO_ONLINE_PROVIDERSTOREPAGE_H
#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/grid.h"
#include "store.h"
#include "GlobalVariables.h"
#include "ModifyProductPage.h"

class ProviderStorePage: public wxDialog{
public:
    ProviderStorePage(const wxString& title);

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

    std::vector<std::vector<std::string>> mat_store;
};

#endif //INGROSSO_ONLINE_PROVIDERSTOREPAGE_H
