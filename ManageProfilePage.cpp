//
// Created by Andrea Lipperi on 31/03/23.
//

#include "ManageProfilePage.h"
#include "GlobalVariables.h"
#include "dbCityManager.h"
#include "user.h"
#include "wx/textctrl.h"


const long ManageProfilePage::IdButtonConfirm =::wxNewId();
const long ManageProfilePage::IdButtonVP =::wxNewId();

BEGIN_EVENT_TABLE (ManageProfilePage, wxFrame)
                EVT_BUTTON(IdButtonConfirm, ManageProfilePage::OnConfirm)
                EVT_BUTTON(IdButtonVP, ManageProfilePage::ViewPass)
END_EVENT_TABLE()

ManageProfilePage::ManageProfilePage(const wxString &title):
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(400, 400)) {
    username=GlobalVariables::GetInstance().GetValueUsername();
    type=GlobalVariables::GetInstance().GetValueType();

    messageError="Password Not Equal";
    messageCorrect="Password Equal";

    wxStaticText *address = new wxStaticText(this, -1, wxT("Address"));
    wxStaticText *city = new wxStaticText(this, -1, wxT("City"));
    wxStaticText *password = new wxStaticText(this, -1, wxT("Password"));
    wxStaticText *usernameText = new wxStaticText(this, -1, wxT("Username"));
    wxStaticText *email=new wxStaticText(this, -1, wxT("Email"));

    City table_city;
    std::vector<std::string> cities;

    cities=table_city.select();
    wxVector<string> choices;
    for (int k=0; k<table_city.number_of_city(); k++){
        choices.push_back(cities[k]);
    }
    wxString myString[table_city.number_of_city()];
    for (int i=0;i<table_city.number_of_city();i++) {
        myString[i].Append(choices[i]);
    }
    cities.clear();
    choices.clear();

    choiceC=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceC->Append("Select");
    choiceC->Append(table_city.number_of_city(),myString);

    Confirm=new wxButton (this,IdButtonConfirm,_T ("Confirm"),wxDefaultPosition,wxDefaultSize,0);
    ViewP=new wxButton (this,IdButtonVP,_T ("View Password"),wxDefaultPosition,wxDefaultSize,0);
    User user;

    data_user=user.select_data(username);

    tcA = new wxTextCtrl(this, wxID_ANY,data_user[0]);
    tcU= new wxTextCtrl(this, wxID_ANY,username);
    tcEm=new wxTextCtrl(this, wxID_ANY,data_user[2]);
    txt_conf_psw = new wxStaticText(this, -1, wxT("Confirm Password"));
    m_passwordText = new wxTextCtrl(this, wxID_ANY, data_user[3], wxDefaultPosition, wxSize(150, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
    m_passwordConf = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(120, wxDefaultSize.GetHeight()), wxTE_PASSWORD);
    m_passwordConf->Bind(wxEVT_TEXT, &ManageProfilePage::OnTextChange, this);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Insert(0,address);
    sizer->Insert(1,tcA, 1, wxALL, 5);
    sizer->Insert(2,city);
    sizer->Insert(3,choiceC,1, wxALL, 5);
    sizer->Insert(4,usernameText);
    sizer->Insert(5,tcU, 1, wxALL, 5);
    sizer->Insert(6,email);
    sizer->Insert(7,tcEm, 1, wxALL, 5);
    sizer->Insert(8,password);
    sizer->Insert(9,m_passwordText,1, wxALL, 5);
    sizer->Insert(10,txt_conf_psw);
    sizer->Insert(11,m_passwordConf,1, wxALL, 5);
    sizer->Insert(12,ViewP,0, wxALL, 5);
    sizer->Insert(13,Confirm,0,wxALL, 5);


    SetSizer(sizer);

    Centre();
}


void ManageProfilePage::OnConfirm(wxCommandEvent &event) {
    if (choiceC->GetSelection() == wxNOT_FOUND)
    {
        wxMessageBox("Choose a city", "Error", wxICON_ERROR);
    } else if (m_passwordConf->IsEmpty()) {
        wxMessageBox("Insert Confirm Password", "Error", wxICON_ERROR);
    } else {
        std::string b_n = data_user[4];
        std::string new_address = tcA->GetValue().ToStdString();
        int id_city = choiceC->GetSelection();
        std::string new_username = tcU->GetValue().ToStdString();
        std::string new_email = tcEm->GetValue().ToStdString();
        std::string new_pass = m_passwordText->GetValue().ToStdString();
        std::string new_pass_conf = m_passwordConf->GetValue().ToStdString();
        int control_digit=0;
        int control_upper=0;
        for(int i=0; i<new_pass.length();i++){
            if (isdigit(new_pass[i])){
                control_digit=control_digit+1;
            }
            if (isupper(new_pass[i])) {
                control_upper=control_upper+1;
            }
        }
        if (control_digit>0 && new_pass.length()>=8 && control_upper>0 && new_pass==new_pass_conf) {
            Close();
            User *user = new User(type, b_n, new_address, new_email, new_pass, new_username, id_city);
            user->changeData(username);
            GlobalVariables::GetInstance().SetValueUsername(user->get_username());
        } else if(new_pass!=new_pass_conf) {
            wxLogMessage("The password and The confirm password must be equal");
        } else {
            wxLogMessage("The password should contain a number, a capital letter and a lenght >= of 8 characters");
        }
    }
}
void ManageProfilePage::ViewPass(wxCommandEvent &event) {
    std::string pass = m_passwordText->GetValue().ToStdString();
    std::string pass_conf = m_passwordConf->GetValue().ToStdString();
    sizer->Hide(m_passwordText);
    sizer->Hide(txt_conf_psw);
    sizer->Hide(m_passwordConf);
    sizer->Hide(txt_message);
    sizer->Hide(ViewP);
    sizer->Hide(Confirm);
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
    txt_conf_psw = new wxStaticText(this, -1, wxT("Confirm Password"));
    m_passwordConf->Bind(wxEVT_TEXT, &ManageProfilePage::OnTextChange, this);
    Confirm=new wxButton (this,IdButtonConfirm,_T ("Confirm"),wxDefaultPosition,wxDefaultSize,0);
    sizer->Insert(9,m_passwordText,1, wxALL, 5);
    sizer->Insert(10,txt_conf_psw);
    sizer->Insert(11,m_passwordConf,1, wxALL, 5);
    sizer->Insert(12,ViewP,0, wxALL, 5);
    sizer->Insert(13,Confirm,0, wxALL, 5);
    wxSize currentSize = GetSize();
    int newWidth = currentSize.GetWidth() +1;
    int newHeight = currentSize.GetHeight() +4;
    SetSize(newWidth, newHeight);

}
void ManageProfilePage::OnTextChange(wxCommandEvent &event) {
    sizer->Hide(txt_message);
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
    sizer->Insert(12,txt_message);
    wxSize currentSize = GetSize();
    int newWidth = currentSize.GetWidth() +1;
    int newHeight = currentSize.GetHeight() +4;
    SetSize(newWidth, newHeight);
}