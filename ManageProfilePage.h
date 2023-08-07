//
// Created by Andrea Lipperi on 31/03/23.
//
/*
#ifndef INGROSSO_ONLINE_MANAGEPROFILEPAGE_H
#define INGROSSO_ONLINE_MANAGEPROFILEPAGE_H

#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/string.h"
#include <string>
#include "HomePageProviders.h"
#include "dbCategoriesManager.h"



class ManageProfilePage : public wxFrame{
public:
    ManageProfilePage(const wxString& title);

    static const long IdButtonConfirm;
    static const long IdButtonVP;
DECLARE_EVENT_TABLE()


private:
    void OnConfirm(wxCommandEvent& event);
    void ViewPass(wxCommandEvent& event);
    void OnTextChange(wxCommandEvent& event);
    wxButton *Confirm;
    wxButton *ViewP;
    std::string username;
    wxBoxSizer *sizer;
    wxChoice* choiceC;
    std::string type;
    vector<string> data_user;
    wxTextCtrl *tcA;
    wxTextCtrl *tcU;
    wxTextCtrl *tcEm;
    wxTextCtrl *m_passwordText;
    std::string messageError;
    std::string messageCorrect;
    std::string txt_button;
    wxStaticText *txt_message;
    wxTextCtrl *m_passwordConf;
    wxStaticText *txt_conf_psw;

};


#endif //INGROSSO_ONLINE_MANAGEPROFILEPAGE_H
*/