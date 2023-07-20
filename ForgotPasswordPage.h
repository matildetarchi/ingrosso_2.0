//
// Created by Andrea Lipperi on 06/05/23.
//

#ifndef INGROSSO_ONLINE_FORGOTPASSWORDPAGE_H
#define INGROSSO_ONLINE_FORGOTPASSWORDPAGE_H

#include <wx/wx.h>
#include "wx/wxhtml.h"

class ForgotPasswordPage : public wxFrame{
public:
    ForgotPasswordPage(const wxString& title);
    static const long IdButtonConfirm;
    static const long IdButtonChange;
    static const long IdButtonBack;
    static const long IdButtonVP;

DECLARE_EVENT_TABLE()

private:
    void Insert(wxCommandEvent& event);
    void Change(wxCommandEvent& event);
    void ComeBack(wxCommandEvent& event);
    void ViewPass(wxCommandEvent& event);
    void OnTextChange(wxCommandEvent& event);
    wxButton *ViewP;
    wxButton *Confirm;
    wxFlexGridSizer *fgs1;
    wxFlexGridSizer *fgs2;
    wxFlexGridSizer *fgs;
    wxButton *Back;
    wxButton *ChangeButton;
    wxStaticText *txt_email;
    wxStaticText *txt_psw;
    wxStaticText *txt_conf_psw;
    wxTextCtrl *m_passwordText;
    wxTextCtrl *m_passwordConf;
    std::string messageError;
    std::string messageCorrect;
    std::string txt_button;
    wxStaticText *txt_message;
    wxTextCtrl *tc1;
};



#endif //INGROSSO_ONLINE_FORGOTPASSWORDPAGE_H
