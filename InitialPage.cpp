//
// Created by dario on 16/11/2022.
//

#include "InitialPage.h"

const long InitialPage::IdButtonRegister =::wxNewId();
const long InitialPage::IdButtonAccess =::wxNewId();

BEGIN_EVENT_TABLE (InitialPage, wxFrame)
                EVT_BUTTON(IdButtonAccess, InitialPage::OnAccess)
                EVT_BUTTON(IdButtonRegister, InitialPage::OnRegister)
END_EVENT_TABLE()


InitialPage::InitialPage(Engine* engine, const wxString &title, const wxPoint &pos, const wxSize &size):
                                            e(engine), wxFrame(nullptr,  - 1, title, pos, size){

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    wxBoxSizer *MainBox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *MainBox1 = new wxBoxSizer(wxHORIZONTAL);
    Register = new wxButton (this,IdButtonRegister,_T ("Register"),wxDefaultPosition,wxSize(180,40),0);
    Enter = new wxButton(this,IdButtonAccess,_T ("Enter"), wxDefaultPosition,wxSize(180,40),0);
    MainBox1->Add(Register,0,wxLEFT,210);
    this->SetSizer(MainBox1);
    MainBox->Add(Enter,0,wxLEFT,210);
    this->SetSizer(MainBox);
    this->Layout();

}


void InitialPage::OnAccess(wxCommandEvent& event )
{

    auto *MainWin2 = new LogInPage(e,_T("ACCESS"));
    MainWin2->Show(TRUE);
}
void InitialPage::OnRegister(wxCommandEvent& event){

    auto *MainWin3 = new RegistrationPage(e,_T("REGISTRATION"));
    MainWin3->Show(TRUE);
}
