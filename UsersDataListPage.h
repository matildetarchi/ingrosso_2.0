//
// Created by Andrea Lipperi on 08/05/23.
//

#ifndef INGROSSO_ONLINE_USERSDATALISTPAGE_H
#define INGROSSO_ONLINE_USERSDATALISTPAGE_H

#include "wx/wxhtml.h"
#include "wx/wx.h"
#include "wx/grid.h"
#include <wx/app.h>
#include <wx/spinctrl.h>
#include "Engine.h"


class UsersDataListPage : public wxFrame {
public:
    UsersDataListPage(Engine *e, const wxString &title, const std::string &var_city);
    static const long IdButtonBack;
    DECLARE_EVENT_TABLE()


private:
    void OnChoice(wxCommandEvent& event);
    void ComeBack(wxCommandEvent& event);
    wxButton *Back;
    wxBoxSizer *sizer;
    wxGrid *grid;
    std::string city;
    std::string type;
    std::string username;
    wxChoice* choiceOrder;
    Engine *engine;
    shared_ptr<User> user;
    shared_ptr<dbUserManager> db_user;
    vector<shared_ptr<User>> user_list;
};

#endif //INGROSSO_ONLINE_USERSDATALISTPAGE_H