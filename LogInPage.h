//
// Created by dario on 16/11/2022.
//


#ifndef BUTTON_WXWIDGETS_NEWFRAME_H
#define BUTTON_WXWIDGETS_NEWFRAME_H

#include "User.h"
#include "HomePageClient.h"
#include "HomePageProviders.h"
#include "InitialPage.h"
#include "ForgotPasswordPage.h"
#include "wx/wx.h"
#include "wx/wxhtml.h"
#include <wx/hyperlink.h>
#include "Engine.h"


class LogInPage : public wxFrame{
public:
    LogInPage(Engine* e, const wxString& title);

    static const long IdButtonConfirm;
    static const long IdButtonBack;
    static const long IdButtonForPsw;
    static const long IdButtonVP;

DECLARE_EVENT_TABLE()

private:
    void Access(wxCommandEvent& event);
    void ForgotPassword(wxCommandEvent& event);
    void ViewPass(wxCommandEvent& event);
    void ComeBack(wxCommandEvent& event);
    wxButton *ViewP;
    wxFlexGridSizer *fgs;
    wxHyperlinkCtrl* hyperlink;
    wxButton *Confirm;
    wxButton *Back;
    wxTextCtrl *m_passwordText;
    wxTextCtrl *tc1;

    Engine* engine;
    shared_ptr<User> user;
};



#endif //BUTTON_WXWIDGETS_NEWFRAME_H
