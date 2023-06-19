//
// Created by dario on 30/11/2022.
//


#ifndef INGROSSO_ONLINE_STOCKISTFRAME_H
#define INGROSSO_ONLINE_STOCKISTFRAME_H
#include "wx/wxhtml.h"
#include "wx/wx.h"
#include "InsertProductPage.h"
#include "ChooseStatusPage.h"
#include "ProviderStorePage.h"
#include "SelectionCityPage.h"
#include "GlobalVariables.h"
#include "ManageProfilePage.h"
#include "InitialPage.h"
#include "user.h"

class HomePageProviders: public wxFrame {
public:
    HomePageProviders(const wxString& title, const wxPoint& pos, const wxSize& size);

    static const long IdButtonRequests;
    static const long IdButtonProfile;
    static const long IdButtonStore;
    static const long IdButtonInsProd;
    static const long IdButtonClients;
    static const long IdButtonRemove;
    static const long IdButtonBack;

DECLARE_EVENT_TABLE()

private:
    void OpenRequests(wxCommandEvent& event);
    void OpenProfile(wxCommandEvent& event);
    void OpenStore(wxCommandEvent& event);
    void ViewClients(wxCommandEvent& event);
    void OpenInsProd(wxCommandEvent& event);
    void RemoveUser(wxCommandEvent& event);
    void ComeBack(wxCommandEvent& event);
    wxButton *Requests;
    wxButton *Profile;
    wxButton *Clients;
    wxButton *Store;
    wxButton *InsProd;
    wxButton *Remove;
    wxButton *Back;
    std::string username;
    std::string type;

};


#endif //INGROSSO_ONLINE_STOCKISTFRAME_H