//
// Created by dario on 09/12/2022.
//

#include "HomePageClient.h"



const long HomePageClient::IdButtonCart =::wxNewId();
const long HomePageClient::IdButtonProfile =::wxNewId();
const long HomePageClient::IdButtonFavorites =::wxNewId();
const long HomePageClient::IdButtonOrders =::wxNewId();
const long HomePageClient::IdButtonProducts =::wxNewId();
const long HomePageClient::IdButtonProviders =::wxNewId();
const long HomePageClient::IdButtonRemove =::wxNewId();
const long HomePageClient::IdButtonComeBack =::wxNewId();




BEGIN_EVENT_TABLE (HomePageClient, wxFrame)

           EVT_BUTTON(IdButtonCart, HomePageClient::OpenCart)
           EVT_BUTTON(IdButtonProfile, HomePageClient::OpenProfile)
           EVT_BUTTON(IdButtonProducts, HomePageClient::OpenProductsList)
           EVT_BUTTON(IdButtonProviders, HomePageClient::ViewProviders)
           EVT_BUTTON(IdButtonOrders, HomePageClient::OpenOrdersList)
           EVT_BUTTON(IdButtonFavorites, HomePageClient::OpenFavoritesList)
           EVT_BUTTON(IdButtonRemove, HomePageClient::RemoveUser)
           EVT_BUTTON(IdButtonComeBack, HomePageClient::ComeBack)

END_EVENT_TABLE()


HomePageClient::HomePageClient(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size){
    username=GlobalVariables::GetInstance().GetValueUsername();
    type=GlobalVariables::GetInstance().GetValueType();


    wxPanel *panelHome = new wxPanel(this, -1);



    wxBoxSizer *box = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer *MainGrid = new wxFlexGridSizer(3, 2, 25, -60);


    Orders=new wxButton (panelHome,IdButtonOrders,_T ("Orders' list"),wxDefaultPosition,wxSize(140,40),0);
    Profile=new wxButton(panelHome,IdButtonProfile, _T("Manage profile"), wxDefaultPosition,wxSize(140,40),0 );
    Products=new wxButton(panelHome, IdButtonProducts, _T("Products' list"), wxDefaultPosition, wxSize(140,40), 0);
    Providers=new wxButton(panelHome, IdButtonProviders, _T("View Providers"), wxDefaultPosition, wxSize(140,40), 0);
    Cart=new wxButton(panelHome, IdButtonCart, _T("Cart"),wxDefaultPosition, wxSize(140,40),0);
    Favorites=new wxButton(panelHome, IdButtonFavorites, _T("Favorites"),wxDefaultPosition, wxSize(140,40),0);
    Remove=new wxButton(panelHome, IdButtonRemove, _T("Delete Account"),wxDefaultPosition, wxDefaultSize,0);
    Back=new wxButton(panelHome,IdButtonComeBack,_T ("Logout"),wxDefaultPosition,wxDefaultSize,0);




    MainGrid->Add(Products,0,wxLEFT, 50);
    MainGrid->Add(Favorites,0,wxLEFT, 50);
    MainGrid->Add(Orders,0,wxLEFT, 50);
    MainGrid->Add(Cart,0,wxLEFT, 50);
    MainGrid->Add(Profile,0,wxLEFT,50);
    MainGrid->Add(Providers,0,wxLEFT,50);
    MainGrid->Add(Remove,0,wxLEFT,90);
    MainGrid->Add(Back,0,wxLEFT, 90);

    MainGrid->AddGrowableRow(1, 1);
    MainGrid->AddGrowableCol(1, 1);


    box->Add(MainGrid, 1, wxALL, 60);



    panelHome->SetSizer(box);
    //this->SetSizer(MainBox);

    Centre();

}

void HomePageClient::OpenProductsList(wxCommandEvent &event) {
    SelectionSubcategoryPage *List = new SelectionSubcategoryPage (_T("SELECT SUBCATEGORY"));
    List->Show(TRUE);
}

void HomePageClient::OpenProfile(wxCommandEvent &event) {
    ManageProfilePage *manage = new ManageProfilePage (_T("MANAGE YOUR PROFILE"));
    manage->Show(TRUE);
}

void HomePageClient::OpenCart(wxCommandEvent &event) {
    CartPage *cart=new CartPage(_T("CART"));
    cart->Show(TRUE);
}

void HomePageClient::OpenFavoritesList(wxCommandEvent &event) {
    FavouritesListPage *fav=new FavouritesListPage(_T("FAVOURITES LIST"));
    fav->Show(TRUE);
}

void HomePageClient::OpenOrdersList(wxCommandEvent &event) {
    ChooseStatusPage *ord= new ChooseStatusPage(_T("ORDERS"));
    ord->Show(TRUE);
}

void HomePageClient::ComeBack(wxCommandEvent &event) {
    GlobalVariables::GetInstance().SetValueUsername("");
    GlobalVariables::GetInstance().SetValueType("");
    Close();
    InitialPage *home = new InitialPage(_T("YOUR MARKET RIGHT HERE"), wxPoint(50, 20), wxSize(500, 300));
    home->Show(TRUE);
}

void HomePageClient::RemoveUser(wxCommandEvent &event) {
    User user;
    if (!user.remove(username, type)){
        wxMessageBox("You can't delete your account because you have orders not accepted/denied", "Error", wxICON_ERROR);
    } else {
        wxMessageBox("Account removed, you'll be sent to registracion page", "Error", wxICON_ERROR);
        GlobalVariables::GetInstance().SetValueUsername("");
        GlobalVariables::GetInstance().SetValueType("");
        Close();
        InitialPage *home = new InitialPage(_T("YOUR MARKET RIGHT HERE"), wxPoint(50, 20), wxSize(500, 300));
        home->Show(TRUE);
    }
}

void HomePageClient::ViewProviders(wxCommandEvent &event) {
    SelectionCityPage *sel_c = new SelectionCityPage(_T("SELECT CITY"));
    sel_c->Show(TRUE);
}
