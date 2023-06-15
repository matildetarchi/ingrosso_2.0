//
// Created by dario on 16/11/2022.
//

#include "InitialPage.h"
#include "wx/wx.h"
#include "LogInPage.h"
#include "MyApp.h"
#include "SelectionSubcategoryPage.h"
#include "RegistrationPage.h"

const long InitialPage::IdButtonRegister=::wxNewId();
const long InitialPage::IdButtonAccess =::wxNewId();
BEGIN_EVENT_TABLE (InitialPage, wxFrame)
                EVT_BUTTON(IdButtonAccess, InitialPage::OnAccess)
                EVT_BUTTON(IdButtonRegister, InitialPage::OnRegister)
END_EVENT_TABLE() // The button is pressed


InitialPage::InitialPage(const wxString &title, const wxPoint &pos, const wxSize
&size): wxFrame(NULL,  - 1, title, pos, size)

{

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    wxBoxSizer *MainBox= new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *MainBox1=new wxBoxSizer(wxHORIZONTAL);
    Register=new wxButton (this,IdButtonRegister,_T ("Register"),wxDefaultPosition,wxSize(180,40),0);
    HelloWorld=new wxButton(this,IdButtonAccess,_T ("Enter"), wxDefaultPosition,wxSize(180,40),0);
    MainBox1->Add(Register,0,wxLEFT,210);
    this->SetSizer(MainBox1);
    MainBox->Add(HelloWorld,0,wxLEFT,210);
    this->SetSizer(MainBox);
    this->Layout();

}


void InitialPage::OnAccess(wxCommandEvent& event )
{
    Close();
    LogInPage *MainWin2 = new LogInPage(_T("ACCESS"));
    MainWin2->Show(TRUE); // show the window
    // and finally, set it as the main window
    // Tells the OS to quit running this process
}
void InitialPage::OnRegister(wxCommandEvent& event){
    Close();
    RegistrationPage *MainWin3 = new RegistrationPage(_T("REGISTRATION"));
    MainWin3->Show(TRUE);
}
