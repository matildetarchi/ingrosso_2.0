//
// Created by dario on 12/11/2022.
//

#ifndef BUTTON_WXWIDGETS_MYFRAME_H
#define BUTTON_WXWIDGETS_MYFRAME_H
#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "Engine.h"
#include "LogInPage.h"
#include "RegistrationPage.h"




class InitialPage: public wxFrame
{
public:
    InitialPage(Engine* engine,const wxString &title, const wxPoint &pos, const wxSize &size );

    static const long IdButtonAccess;
    static const long IdButtonRegister;

DECLARE_EVENT_TABLE()
private:
    void OnAccess( wxCommandEvent& event );
    void OnRegister(wxCommandEvent& event);
    wxButton *Enter;
    wxButton *Register;
    static std::string username_actual_user;
    Engine *e;
};

enum
{
    BUTTON_Hello = wxID_HIGHEST + 1
};

#endif
