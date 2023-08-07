//
// Created by Andrea Lipperi on 06/05/23.
//
/*
#include "ForgotPasswordPage.h"




const long ForgotPasswordPage::IdButtonConfirm =::wxNewId();
const long ForgotPasswordPage::IdButtonChange =::wxNewId();
const long ForgotPasswordPage::IdButtonBack =::wxNewId();
const long ForgotPasswordPage::IdButtonVP =::wxNewId();

BEGIN_EVENT_TABLE (ForgotPasswordPage, wxFrame)
                EVT_BUTTON(IdButtonConfirm, ForgotPasswordPage::Insert)
                EVT_BUTTON(IdButtonChange, ForgotPasswordPage::Change)
                EVT_BUTTON(IdButtonBack, ForgotPasswordPage::ComeBack)
                EVT_BUTTON(IdButtonVP, ForgotPasswordPage::ViewPass)

END_EVENT_TABLE() // The button is pressed


ForgotPasswordPage::ForgotPasswordPage(Engine *engine, const wxString &title)
        : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)){

        wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

        fgs2 = new wxFlexGridSizer(3, 2, 12, 5);
        fgs = new wxFlexGridSizer(9, 1, 12, -5);

        messageError="Password Not Equal";
        messageCorrect="Password Equal";
        txt_email = new wxStaticText(this, -1, wxT("Email"));
        Confirm=new wxButton (this,IdButtonConfirm,_T ("Ok"),wxDefaultPosition,wxDefaultSize,0);
        Back=new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

        tc1 = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxSize(200, wxDefaultSize.GetHeight()));


        fgs->Add(txt_email);
        fgs->Add(tc1, 0, wxEXPAND, 5);
        fgs->Add(Confirm,0);
        fgs->Add(Back,0);

        fgs->AddGrowableRow(1, 1);
        fgs->AddGrowableCol(1, 1);


        hbox->Add(fgs, 1, wxALL, 5);

        SetSizer(hbox);

        Centre();

}

void ForgotPasswordPage::Insert(wxCommandEvent &event){
    if (tc1->IsEmpty()){
        wxMessageBox("Insert your email", "Error", wxICON_ERROR);
    } else {
        std::string e = tc1->GetValue().ToStdString();
        int result;

        result = engine->access_reg(e, "", 1);
        if (!result) {
            wxLogMessage("There is no account with this email");
        } else {

            fgs->DeleteWindows();
            txt_psw = new wxStaticText(this, -1, wxT("New Password"));
            txt_conf_psw = new wxStaticText(this, -1, wxT("Confirm Password"));
            ChangeButton=new wxButton (this,IdButtonChange,_T ("Ok"),wxDefaultPosition,wxDefaultSize,0);
            ViewP=new wxButton (this,IdButtonVP,_T ("View Password"),wxDefaultPosition,wxDefaultSize,0);
            m_passwordText = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(120, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
            m_passwordConf = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(120, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
            m_passwordConf->Bind(wxEVT_TEXT, &ForgotPasswordPage::OnTextChange, this);
            Back=new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

            fgs->Add(fgs2);
            fgs2->Add(txt_psw);
            fgs2->Add(m_passwordText,0, wxEXPAND);
            fgs2->Add(txt_conf_psw);
            fgs2->Add(m_passwordConf,0,wxEXPAND);
            fgs->Add(ViewP,0);
            fgs->Add(ChangeButton,0);
            fgs->Add(Back,0);
            fgs->Layout();
            wxSize currentSize = GetSize();
            int newWidth = currentSize.GetWidth() +1;
            int newHeight = currentSize.GetHeight() +1;
            SetSize(newWidth, newHeight);

        }
    }
}

void ForgotPasswordPage::Change(wxCommandEvent &event) {
    if (m_passwordText->IsEmpty()){
        wxMessageBox("Insert Password.", "Error", wxICON_ERROR);
    } else {
        std::string psw = m_passwordText->GetValue().ToStdString();
        std::string psw_conf = m_passwordConf->GetValue().ToStdString();
        int control_digit=0;
        int control_upper=0;
        for(int i=0; i<psw.length();i++){
            if (isdigit(psw[i])){
                control_digit=control_digit+1;
            }
            if (isupper(psw[i])) {
                control_upper=control_upper+1;
            }
        }
        if (control_digit>0 && psw.length()>=8 && control_upper>0 && psw==psw_conf) {
            User user;
            user.changePsw(tc1->GetValue().ToStdString(), psw);
            Close();
            wxLogMessage("Password Changed");
            LogInPage *MainWin2 = new LogInPage(_T("ACCESS"));
            MainWin2->Show(TRUE);
        } else {
            wxLogMessage("The password should contain a number, a capital letter and a lenght >= of 8 characters");
        }
    }
}

void ForgotPasswordPage::ComeBack(wxCommandEvent &event) {
    Close();
    LogInPage *MainWin2 = new LogInPage(_T("ACCESS"));
    MainWin2->Show(TRUE);
}
void ForgotPasswordPage::ViewPass(wxCommandEvent &event) {
    std::string pass = m_passwordText->GetValue().ToStdString();
    std::string passConf = m_passwordConf->GetValue().ToStdString();
    int control;
    string txt_button;
    if (m_passwordText->GetWindowStyle() & wxTE_PASSWORD) {
        control = 0;
        txt_button ="Hide Password";
        } else {
        control = 1;
        txt_button="View Password";
    }
    fgs->DeleteWindows();
    txt_psw = new wxStaticText(this, -1, wxT("New Password"));
    if (control==0){
        m_passwordText = new wxTextCtrl(this, wxID_ANY, pass, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PROCESS_ENTER);
        m_passwordConf = new wxTextCtrl(this, wxID_ANY, passConf, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PROCESS_ENTER);
    } else {
        m_passwordText=new wxTextCtrl(this, wxID_ANY, pass, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
        m_passwordConf = new wxTextCtrl(this, wxID_ANY, passConf, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
    }
    m_passwordConf->Bind(wxEVT_TEXT, &ForgotPasswordPage::OnTextChange, this);
    txt_conf_psw = new wxStaticText(this, -1, wxT("Confirm Password"));
    ViewP=new wxButton (this,IdButtonVP,txt_button,wxDefaultPosition,wxDefaultSize,0);
    ChangeButton=new wxButton (this,IdButtonChange,_T ("Ok"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    fgs2->Insert(0,txt_psw);
    fgs2->Insert(1,m_passwordText,0, wxEXPAND);
    fgs2->Insert(2,txt_conf_psw);
    fgs2->Insert(3,m_passwordConf,0,wxEXPAND);
    fgs->Insert(5,ViewP,0);
    fgs->Insert(6,ChangeButton,0);
    fgs->Insert(7,Back,0);
    wxSize currentSize = GetSize();
    int newWidth = currentSize.GetWidth() +1;
    int newHeight = currentSize.GetHeight() +1;
    SetSize(newWidth, newHeight);

}

void ForgotPasswordPage::OnTextChange(wxCommandEvent &event) {
    fgs2->Hide(txt_message);
    std::string pass = m_passwordText->GetValue().ToStdString();
    txt_message = new wxStaticText(this, -1, wxT(""));
    std::string passConf = m_passwordConf->GetValue().ToStdString();
    if (pass==passConf) {
        txt_message->SetLabel(messageCorrect);
        txt_message->SetOwnForegroundColour(wxColour(0,200,0));
    } else {
        txt_message->SetLabel(messageError);
        txt_message->SetOwnForegroundColour(wxColour(200,0,0));
    }
    fgs2->Insert(4,txt_message);
    wxSize currentSize = GetSize();
    int newWidth = currentSize.GetWidth() +1;
    int newHeight = currentSize.GetHeight() +1;
    SetSize(newWidth, newHeight);
}
*/