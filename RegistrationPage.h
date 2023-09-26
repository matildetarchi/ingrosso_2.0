
//
// Created by dario on 23/11/2022.
//

#ifndef BUTTON_WXWIDGETS_REGISTERFRAME_H
#define BUTTON_WXWIDGETS_REGISTERFRAME_H
#include "wx/wxhtml.h"
#include "wx/wx.h"
#include "Engine.h"


class RegistrationPage : public wxFrame{
public:
    RegistrationPage(Engine* e, const wxString& title);

    static const long IdButtonConfirm;
    static const long IdButtonBack;
    static const long IdButtonProvider;
    static const long IdButtonVP;
    static const long IdButtonClient;
DECLARE_EVENT_TABLE()


private:
    void Register(wxCommandEvent& event);
    void IsProvider(wxCommandEvent& event);
    void IsClient(wxCommandEvent& event);
    void ViewPass(wxCommandEvent& event);
    void ComeBack(wxCommandEvent& event);
    void OnTextChange(wxCommandEvent& event);
    wxFlexGridSizer *fgs;
    wxButton *Confirm;
    wxButton *ViewP;
    wxButton *Back;
    wxRadioButton *Prov;
    wxRadioButton *Cli;
    std::string t;
    wxChoice* choiceC;
    wxTextCtrl *tcB_n;
    wxTextCtrl *tcA;
    wxTextCtrl *tcC;
    wxTextCtrl *tcU;
    wxTextCtrl *tcEm;
    wxTextCtrl *m_passwordText;
    std::string messageError;
    std::string messageCorrect;
    std::string txt_button;
    wxStaticText *txt_message;
    wxTextCtrl *m_passwordConf;
    wxStaticText *txt_conf_psw;
    Engine *engine;

};


#endif //BUTTON_WXWIDGETS_REGISTERFRAME_H
