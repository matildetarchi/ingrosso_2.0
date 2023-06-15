//
// Created by dario on 09/12/2022.
//

//
// Created by dario on 16/11/2022.
//

#include "InitialPage.h"
#include "ForgotPasswordPage.h"
#include "GlobalVariables.h"
#include "wx/wx.h"
#include "LogInPage.h"
#include "MyApp.h"
#include "SelectionSubcategoryPage.h"
#include "user.h"
#include "HomePageClient.h"
#include "HomePageProviders.h"



const long LogInPage::IdButtonConfirm =::wxNewId();
const long LogInPage::IdButtonBack =::wxNewId();
const long LogInPage::IdButtonForPsw =::wxNewId();
const long LogInPage::IdButtonVP =::wxNewId();

BEGIN_EVENT_TABLE (LogInPage, wxFrame)
                EVT_BUTTON(IdButtonConfirm, LogInPage::Access)
                EVT_BUTTON(IdButtonBack, LogInPage::ComeBack)
                EVT_BUTTON(IdButtonForPsw, LogInPage::ForgotPassword)
                EVT_BUTTON(IdButtonVP, LogInPage::ViewPass)

END_EVENT_TABLE() // The button is pressed


LogInPage::LogInPage(const wxString &title)
        : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(400, 350)){

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    fgs = new wxFlexGridSizer(9, 1, 12, -5);


    wxStaticText *thetitle = new wxStaticText(this, -1, wxT("Email"));
    wxStaticText *password = new wxStaticText(this, -1, wxT("Password"));
    ViewP=new wxButton (this,IdButtonVP,_T ("View Password"),wxDefaultPosition,wxDefaultSize,0);
    Confirm=new wxButton (this,IdButtonConfirm,_T ("Ok"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);



    tc1 = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxSize(180, wxDefaultSize.GetHeight()));
    m_passwordText = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PASSWORD);


    // Creare un controllo wxHyperlinkCtrl che apre il frame di destinazione
    hyperlink = new wxHyperlinkCtrl(this, wxID_ANY, "Forgot Password?", "", wxDefaultPosition, wxDefaultSize, wxHL_ALIGN_LEFT);
    hyperlink->SetNormalColour(wxColour(255, 0, 0));
    hyperlink->SetHoverColour(wxColour(0, 200, 0));
    hyperlink->Bind(wxEVT_HYPERLINK, &LogInPage::ForgotPassword, this);


    fgs->Add(thetitle);
    fgs->Add(tc1, 1, wxEXPAND);
    fgs->Add(password);
    fgs->Add(m_passwordText, 1);
    fgs->Add(ViewP,0);
    fgs->Add(Confirm,0);
    fgs->Add(Back,0);
    fgs->Add(hyperlink,0);

    fgs->AddGrowableRow(1, 1);
    fgs->AddGrowableCol(1, 1);


    hbox->Add(fgs, 1, wxALL, 15);

    SetSizer(hbox);

    Centre();



}

void LogInPage::Access(wxCommandEvent &event) {
    if (tc1->IsEmpty() || m_passwordText->IsEmpty()){
        wxMessageBox("Insert every value", "Error", wxICON_ERROR);
    } else {
        std::string e = tc1->GetValue().ToStdString();
        std::string p = m_passwordText->GetValue().ToStdString();
        int result;
        User user;
        result = user.access_reg(e, p, 0);
        if (!result) {
            wxLogMessage("Incorrect email or password");
        } else {
            Close();
            std::string TypeUser;
            TypeUser = user.select_type(e);
            std::string username=user.select_username(e);
            GlobalVariables::GetInstance().SetValueUsername(username);
            GlobalVariables::GetInstance().SetValueType(TypeUser);
            if (TypeUser == "F") {
                HomePageProviders *ProvidersWin = new HomePageProviders(_T("HOME"), wxPoint(50, 20), wxSize(500, 350));
                ProvidersWin->Show(TRUE);
            } else {
                HomePageClient *ClientWin = new HomePageClient(_T("HOME"), wxPoint(50, 20), wxSize(500, 350));
                ClientWin->Show(TRUE);
            }
        }
    }
}

void LogInPage::ComeBack(wxCommandEvent &event) {
    Close();
    InitialPage *home = new InitialPage(_T("YOUR MARKET RIGHT HERE"), wxPoint(50, 20), wxSize(500, 350));
    home->Show(TRUE);
}

void LogInPage::ForgotPassword(wxCommandEvent &event) {
    Close();
    ForgotPasswordPage *forpsw = new ForgotPasswordPage(_T("FORGOT PASSWORD"));
    forpsw->Show(TRUE);
}

void LogInPage::ViewPass(wxCommandEvent &event) {
    fgs->Hide(m_passwordText);
    fgs->Hide(ViewP);
    fgs->Hide(Confirm);
    fgs->Hide(Back);
    fgs->Hide(hyperlink);
    std::string pass = m_passwordText->GetValue().ToStdString();
    if (m_passwordText->GetWindowStyle() & wxTE_PASSWORD) {
        // Impostazione della proprietà wxTE_PROCESS_ENTER per visualizzare il testo
        m_passwordText=new wxTextCtrl(this, wxID_ANY, pass, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PROCESS_ENTER);
        ViewP=new wxButton (this,IdButtonVP,_T ("Hide Password"),wxDefaultPosition,wxDefaultSize,0);
    } else {
        // Impostazione della proprietà wxTE_PASSWORD per nascondere il testo
        m_passwordText=new wxTextCtrl(this, wxID_ANY, pass, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
        ViewP=new wxButton (this,IdButtonVP,_T ("View Password"),wxDefaultPosition,wxDefaultSize,0);
    }
    Confirm=new wxButton (this,IdButtonConfirm,_T ("Confirm"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);
    hyperlink = new wxHyperlinkCtrl(this, wxID_ANY, "Forgot Password?", "", wxDefaultPosition, wxDefaultSize, wxHL_ALIGN_LEFT);
    hyperlink->SetNormalColour(wxColour(255, 0, 0));
    hyperlink->SetHoverColour(wxColour(0, 200, 0));
    hyperlink->Bind(wxEVT_HYPERLINK, &LogInPage::ForgotPassword, this);
    fgs->Add(m_passwordText,1, wxALL, 5);
    fgs->Add(ViewP,0);
    fgs->Add(Confirm,0);
    fgs->Add(Back,0);
    fgs->Add(hyperlink,0);
    wxSize currentSize = GetSize();
    int newWidth = currentSize.GetWidth() +1;
    int newHeight = currentSize.GetHeight() +1;
    SetSize(newWidth, newHeight);

}
