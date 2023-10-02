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


HomePageClient::HomePageClient(Engine *engine, const wxString& title, const wxPoint& pos, const wxSize& size): eng(engine),
         wxFrame(nullptr, wxID_ANY, title, pos, size){

    client = eng->get_client();

    username = client->get_username();
    type = client->get_type();
    db_user = engine->get_db_user();


    auto *panelHome = new wxPanel(this, -1);

    auto *box = new wxBoxSizer(wxHORIZONTAL);
    auto *MainGrid = new wxFlexGridSizer(4, 2, 25, -60);


    Orders = new wxButton (panelHome,IdButtonOrders,_T ("Orders' list"),wxDefaultPosition,wxSize(140,40),0);
    Profile = new wxButton(panelHome,IdButtonProfile, _T("Manage profile"), wxDefaultPosition,wxSize(140,40),0 );
    Products = new wxButton(panelHome, IdButtonProducts, _T("Products' list"), wxDefaultPosition, wxSize(140,40), 0);
    Providers = new wxButton(panelHome, IdButtonProviders, _T("View Providers"), wxDefaultPosition, wxSize(140,40), 0);
    Cart = new wxButton(panelHome, IdButtonCart, _T("Cart"),wxDefaultPosition, wxSize(140,40),0);
    Favorites = new wxButton(panelHome, IdButtonFavorites, _T("Favorites"),wxDefaultPosition, wxSize(140,40),0);
    Remove = new wxButton(panelHome, IdButtonRemove, _T("Delete Account"),wxDefaultPosition, wxDefaultSize,0);
    Back = new wxButton(panelHome,IdButtonComeBack,_T ("Logout"),wxDefaultPosition,wxDefaultSize,0);




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

    Centre();

}

void HomePageClient::OpenProductsList(wxCommandEvent &event) {
    auto *List = new SelectionSubcategoryPage (eng, _T("SELECT SUBCATEGORY"));
    List->Show(TRUE);
}

void HomePageClient::OpenProfile(wxCommandEvent &event) {
    auto *manage = new ManageProfilePage (eng, _T("MANAGE YOUR PROFILE"));
    manage->Show(TRUE);
}

void HomePageClient::OpenCart(wxCommandEvent &event) {
    auto *cart = new CartPage(eng, _T("CART"));
    cart->Show(TRUE);
}

void HomePageClient::OpenFavoritesList(wxCommandEvent &event) {
    auto *fav = new FavouritesListPage(eng, _T("FAVOURITES LIST"));
    fav->Show(TRUE);
}

void HomePageClient::OpenOrdersList(wxCommandEvent &event) {
    auto *EnterWin = new ChooseStatusPage (eng, _T("REQUESTS"));
    EnterWin->Show(TRUE);
}

void HomePageClient::ComeBack(wxCommandEvent &event) {
    Close();
}

void HomePageClient::RemoveUser(wxCommandEvent &event) {

    if (!db_user->remove_from_db(username, type)){
        wxMessageBox("You can't delete your account because you have orders not accepted/denied", "Error", wxICON_ERROR);
    } else {
        wxMessageBox("Account removed, you'll be sent to registracion page", "Error", wxICON_ERROR);
        client->delete_objects_of_user();
        Close();
    }
}

void HomePageClient::ViewProviders(wxCommandEvent &event) {
    auto *sel_c = new SelectionCityPage(eng, _T("SELECT CITY"));
    sel_c->Show(TRUE);
}
