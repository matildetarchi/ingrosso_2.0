//
// Created by dario on 16/11/2022.
//

#include <wx/wx.h>
#include "wx/wxhtml.h"
#include <wx/hyperlink.h>
#ifndef BUTTON_WXWIDGETS_NEWFRAME_H
#define BUTTON_WXWIDGETS_NEWFRAME_H


class LogInPage : public wxFrame{
public:
    LogInPage(const wxString& title);
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
};



#endif //BUTTON_WXWIDGETS_NEWFRAME_H