//
// Created by dario on 30/11/2022.
//

#include "HomePageProviders.h"
#include "ChooseStatusPage.h"
#include "ProviderStorePage.h"
#include "SelectionCityPage.h"
#include "GlobalVariables.h"
#include "ManageProfilePage.h"
#include "InitialPage.h"
#include "User.h"

const long HomePageProviders::IdButtonStore =::wxNewId();
const long HomePageProviders::IdButtonProfile =::wxNewId();
const long HomePageProviders::IdButtonInsProd =::wxNewId();
const long HomePageProviders::IdButtonRequests =::wxNewId();
const long HomePageProviders::IdButtonClients =::wxNewId();
const long HomePageProviders::IdButtonRemove =::wxNewId();
const long HomePageProviders::IdButtonBack =::wxNewId();


BEGIN_EVENT_TABLE (HomePageProviders, wxFrame)
EVT_BUTTON(IdButtonStore, HomePageProviders::OpenStore)
EVT_BUTTON(IdButtonProfile, HomePageProviders::OpenProfile)
EVT_BUTTON(IdButtonInsProd, HomePageProviders::OpenInsProd)
EVT_BUTTON(IdButtonRequests, HomePageProviders::OpenRequests)
EVT_BUTTON(IdButtonClients, HomePageProviders::ViewClients)
EVT_BUTTON(IdButtonRemove, HomePageProviders::RemoveUser)
EVT_BUTTON(IdButtonBack, HomePageProviders::ComeBack)
END_EVENT_TABLE()


HomePageProviders::HomePageProviders(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size){

    wxPanel *panelHome = new wxPanel(this, -1);

    username=GlobalVariables::GetInstance().GetValueUsername();
    type=GlobalVariables::GetInstance().GetValueType();

    wxBoxSizer *box = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer *MainGrid = new wxFlexGridSizer(2, 2, 25, -5);

    Requests=new wxButton (panelHome,IdButtonRequests,_T ("Manage requests"),wxDefaultPosition,wxSize(180,40),0);
    Profile=new wxButton(panelHome,IdButtonProfile, _T("Manage profile"), wxDefaultPosition,wxSize(180,40),0 );
    InsProd=new wxButton(panelHome, IdButtonInsProd, _T("Insert products"), wxDefaultPosition, wxSize(180,40), 0);
    Store=new wxButton(panelHome, IdButtonStore, _T("Store"),wxDefaultPosition, wxSize(180,40),0);
    Clients=new wxButton(panelHome, IdButtonClients, _T("View Clients"),wxDefaultPosition, wxSize(180,40),0);
    Remove=new wxButton(panelHome, IdButtonRemove, _T("Delete Account"),wxDefaultPosition, wxSize(180,40),0);
    Back=new wxButton(panelHome,IdButtonBack,_T ("Logout"),wxDefaultPosition,wxDefaultSize,0);


    MainGrid->Add(InsProd,0,wxLEFT, 10);
    MainGrid->Add(Profile,0,wxLEFT, 10);
    MainGrid->Add(Store,0, wxLEFT, 10);
    MainGrid->Add(Requests,0,wxLEFT, 10);
    MainGrid->Add(Clients,0,wxLEFT, 10);
    MainGrid->Add(Remove,0,wxLEFT, 10);
    MainGrid->Add(Back,0,wxLEFT, 90);


    MainGrid->AddGrowableRow(1, 1);
    MainGrid->AddGrowableCol(1, 1);


    box->Add(MainGrid, 1, wxALL, 60);



    panelHome->SetSizer(box);

    Centre();

}

void HomePageProviders::OpenRequests(wxCommandEvent &event) {
    ChooseStatusPage *EnterWin = new ChooseStatusPage (_T("REQUESTS"));
    EnterWin->Show(TRUE);
}

void HomePageProviders::OpenProfile(wxCommandEvent &event) {
    ManageProfilePage *manage = new ManageProfilePage (_T("MANAGE PROFILE"));
    manage->Show(TRUE);
}

void HomePageProviders::OpenStore(wxCommandEvent &event) {
    ProviderStorePage *store = new ProviderStorePage(_T("STORE"));
    store->Show(TRUE);
}

void HomePageProviders::OpenInsProd(wxCommandEvent &event) {
    InsertProductPage *EnterWin = new InsertProductPage (_T("NEW PRODUCT"));
    EnterWin->Show(TRUE);
}
void HomePageProviders::ComeBack(wxCommandEvent &event) {
    GlobalVariables::GetInstance().SetValueUsername("");
    GlobalVariables::GetInstance().SetValueType("");
    Close();
    InitialPage *home = new InitialPage(_T("YOUR MARKET RIGHT HERE"), wxPoint(50, 20), wxSize(500, 300));
    home->Show(TRUE);
}
void HomePageProviders::RemoveUser(wxCommandEvent &event)  {
    User user;
    if (!user.remove(username, type)){
        wxMessageBox("You can't delete your account because you have orders not accepted/denied or some of your product are in someone's favourites or cart", "Error", wxICON_ERROR);
    } else {
        wxMessageBox("Account removed, you'll be sent to registracion page", "Error", wxICON_ERROR);
        GlobalVariables::GetInstance().SetValueUsername("");
        GlobalVariables::GetInstance().SetValueType("");
        Close();
        InitialPage *home = new InitialPage(_T("YOUR MARKET RIGHT HERE"), wxPoint(50, 20), wxSize(500, 300));
        home->Show(TRUE);
    }
}

void HomePageProviders::ViewClients(wxCommandEvent &event) {
    SelectionCityPage *sel_c = new SelectionCityPage(_T("SELECT CITY"));
    sel_c->Show(TRUE);
}