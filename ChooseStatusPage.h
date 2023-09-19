//
// Created by Andrea Lipperi on 04/05/23.
//

#ifndef INGROSSO_ONLINE_CHOOSESTATUSPAGE_H
#define INGROSSO_ONLINE_CHOOSESTATUSPAGE_H


#include "OrderHistoryForClientPage.h"
#include "ManageRequestPage.h"
#include "User.h"

class ChooseStatusPage : public wxFrame {
public:
    ChooseStatusPage(Engine* e, const wxString &title);

    static const long IdButtonInsert;
    static const long IdButtonComeBack;


    DECLARE_EVENT_TABLE()
private:
    void ComeBack(wxCommandEvent& event);
    void InsertProduct(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    wxButton *Insert;
    wxBoxSizer *sizer;
    wxButton *Back;
    wxChoice* choice;
    std::string type;
    Engine* engine;
    std::shared_ptr<User> user;
};

#endif //INGROSSO_ONLINE_CHOOSESTATUSPAGE_H
