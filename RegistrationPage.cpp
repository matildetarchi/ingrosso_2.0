//
// Created by dario on 23/11/2022.
//


/*#include "wx/wx.h"
#include "RegistrationPage.h"
#include "User.h"
#include "dbCityManager.h"
#include "InitialPage.h"

const long RegistrationPage::IdButtonConfirm =::wxNewId();
const long RegistrationPage::IdButtonProvider =::wxNewId();
const long RegistrationPage::IdButtonBack =::wxNewId();
const long RegistrationPage::IdButtonClient =::wxNewId();
const long RegistrationPage::IdButtonVP =::wxNewId();

BEGIN_EVENT_TABLE (RegistrationPage, wxFrame)
        EVT_BUTTON(IdButtonConfirm, RegistrationPage::Register)
        EVT_BUTTON(IdButtonBack, RegistrationPage::ComeBack)
        EVT_RADIOBUTTON(IdButtonClient, RegistrationPage::IsClient)
        EVT_RADIOBUTTON(IdButtonProvider, RegistrationPage::IsProvider)
        EVT_BUTTON(IdButtonVP, RegistrationPage::ViewPass)
END_EVENT_TABLE()

RegistrationPage::RegistrationPage(const wxString &title):
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 700)) {
    messageError="Password Not Equal";
    messageCorrect="Password Equal";
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    wxFlexGridSizer *fgs1=new wxFlexGridSizer(1,2, 12,-5);

    fgs = new wxFlexGridSizer(20, 1, 12, -5);

    dbCityManager table;
    std::vector<std::string> cities;

    cities=table.select();
    wxVector<string> choices;
    for (int k=0; k<table.number_of_city(); k++){
        choices.push_back(cities[k]);
    }
    wxString myString[table.number_of_city()];
    for (int i=0;i<table.number_of_city();i++) {
        myString[i].Append(choices[i]);
    }
    cities.clear();
    choices.clear();

    choiceC=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceC->Append("Select");
    choiceC->Append(table.number_of_city(),myString);

    wxStaticText *type = new wxStaticText(this, -1, wxT("Type"));
    wxStaticText *business_name = new wxStaticText(this, -1, wxT("Business name"));
    wxStaticText *address = new wxStaticText(this, -1, wxT("Address"));
    wxStaticText *city = new wxStaticText(this, -1, wxT("City"));
    wxStaticText *password = new wxStaticText(this, -1, wxT("Password"));
    wxStaticText *username = new wxStaticText(this, -1, wxT("Username"));
    wxStaticText *email=new wxStaticText(this, -1, wxT("Email"));

    Confirm=new wxButton (this,IdButtonConfirm,_T ("Ok"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);
    Provider=new wxRadioButton(this,IdButtonProvider, _T("Provider"), wxDefaultPosition,wxDefaultSize,0 );
    ViewP=new wxButton (this,IdButtonVP,_T ("View Password"),wxDefaultPosition,wxDefaultSize,0);
    Client=new wxRadioButton(this, IdButtonClient, _T("Client"), wxDefaultPosition, wxDefaultSize, 0);
    m_passwordConf = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(120, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
    m_passwordConf->Bind(wxEVT_TEXT, &RegistrationPage::OnTextChange, this);
    txt_conf_psw = new wxStaticText(this, -1, wxT("Confirm Password"));


    tcB_n = new wxTextCtrl(this, -1);
    tcA = new wxTextCtrl(this, -1);
    tcU= new wxTextCtrl(this, -1);
    tcEm=new wxTextCtrl(this, -1);
    m_passwordText = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PASSWORD);

    fgs1->Add(Provider,0);
    fgs1->Add(Client,0, wxLEFT, 70);
    fgs->Add(type);
    fgs->Insert(1,fgs1);
    fgs->Insert(2,business_name);
    fgs->Insert(3,tcB_n,1, wxEXPAND);
    fgs->Insert(4,address);
    fgs->Insert(5,tcA, 1, wxEXPAND);
    fgs->Insert(6,city);
    fgs->Insert(7,choiceC, 1, wxEXPAND);
    fgs->Insert(8,username);
    fgs->Insert(9,tcU, 1, wxEXPAND);
    fgs->Insert(10,email);
    fgs->Insert(11,tcEm, 1, wxEXPAND);
    fgs->Insert(12,password);
    fgs->Insert(13,m_passwordText, 1);
    fgs->Insert(14,txt_conf_psw);
    fgs->Insert(15,m_passwordConf, 1);
    fgs->Insert(16,ViewP,0);
    fgs->Insert(17,Confirm,0);
    fgs->Insert(18,Back,0);


    fgs->AddGrowableRow(1, 1);
    fgs->AddGrowableCol(1, 1);


    hbox->Add(fgs, 1, wxALL, 10);

    SetSizer(hbox);

    Centre();
}



void RegistrationPage::IsProvider(wxCommandEvent& event) {
    t="F";
}

void RegistrationPage::IsClient(wxCommandEvent& event) {
    t="C";
}




void RegistrationPage::Register(wxCommandEvent &event) {
    if (t=="" || tcB_n->IsEmpty() || tcA->IsEmpty() || choiceC->GetSelection() == wxNOT_FOUND || tcU->IsEmpty() || tcEm->IsEmpty() || m_passwordText->IsEmpty() || m_passwordConf->IsEmpty()){
        wxMessageBox("Insert every data.", "Error", wxICON_ERROR);
    } else {

        std::string b_n = tcB_n->GetValue().ToStdString();
        std::string a = tcA->GetValue().ToStdString();
        int id_city = choiceC->GetSelection();
        string city_name=choiceC->GetString(id_city).ToStdString();
        std::string u = tcU->GetValue().ToStdString();
        std::string em = tcEm->GetValue().ToStdString();
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

            Engine *engine;
            User *user = new User(t, b_n, a, em, psw, u, city_name);
            if (engine->doRegistration(user)) {
                Close();
                InitialPage *home = new InitialPage(_T("YOUR MARKET RIGHT HERE"), wxPoint(50, 20), wxSize(500, 300));
                home->Show(TRUE);
            } else {
                wxLogMessage("There is already an account with this email");
            }
        } else if(psw!=psw_conf) {
            wxLogMessage("The password and the confirm password must be equal");
        } else {
            wxLogMessage("The password should contain a number, a capital letter and a lenght >= of 8 characters");
        }
    }

}
void RegistrationPage::ComeBack(wxCommandEvent &event) {
    Close();
    InitialPage *home = new InitialPage(_T("YOUR MARKET RIGHT HERE"), wxPoint(50, 20), wxSize(500, 300));
    home->Show(TRUE);
}
void RegistrationPage::ViewPass(wxCommandEvent &event) {
    fgs->Hide(m_passwordText);
    fgs->Hide(txt_conf_psw);
    fgs->Hide(txt_message);
    fgs->Hide(m_passwordConf);
    fgs->Hide(ViewP);
    fgs->Hide(Confirm);
    fgs->Hide(Back);
    std::string pass = m_passwordText->GetValue().ToStdString();
    std::string pass_conf = m_passwordConf->GetValue().ToStdString();
    if (m_passwordText->GetWindowStyle() & wxTE_PASSWORD) {
        // Impostazione della proprietà wxTE_PROCESS_ENTER per visualizzare il testo
        m_passwordText=new wxTextCtrl(this, wxID_ANY, pass, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PROCESS_ENTER);
        m_passwordConf = new wxTextCtrl(this, wxID_ANY, pass_conf, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PROCESS_ENTER);
        ViewP=new wxButton (this,IdButtonVP,_T ("Hide Password"),wxDefaultPosition,wxDefaultSize,0);
    } else {
        // Impostazione della proprietà wxTE_PASSWORD per nascondere il testo
        m_passwordText=new wxTextCtrl(this, wxID_ANY, pass, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
        m_passwordConf = new wxTextCtrl(this, wxID_ANY, pass_conf, wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
        ViewP=new wxButton (this,IdButtonVP,_T ("View Password"),wxDefaultPosition,wxDefaultSize,0);
    }
    m_passwordConf->Bind(wxEVT_TEXT, &RegistrationPage::OnTextChange, this);
    txt_conf_psw = new wxStaticText(this, -1, wxT("Confirm Password"));
    Confirm=new wxButton (this,IdButtonConfirm,_T ("Ok"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton (this,IdButtonBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);
    fgs->Insert(13,m_passwordText, 1);
    fgs->Insert(14,txt_conf_psw);
    fgs->Insert(15,m_passwordConf, 1);
    fgs->Insert(16,ViewP,0);
    fgs->Insert(17,Confirm,0);
    fgs->Insert(18,Back,0);
    wxSize currentSize = GetSize();
    int newWidth = currentSize.GetWidth() +1;
    int newHeight = currentSize.GetHeight() +1;
    SetSize(newWidth, newHeight);

}


void RegistrationPage::OnTextChange(wxCommandEvent &event) {
    fgs->Hide(txt_message);
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
    fgs->Insert(16,txt_message);
    wxSize currentSize = GetSize();
    int newWidth = currentSize.GetWidth() +1;
    int newHeight = currentSize.GetHeight() +4;
    SetSize(newWidth, newHeight);
}*/