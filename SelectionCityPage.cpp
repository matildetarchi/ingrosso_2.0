//
// Created by Andrea Lipperi on 08/05/23.
//

#include "SelectionCityPage.h"
#include "city.h"
#include "UsersDataListPage.h"
#include "categories.h"
#include "ProductListPage.h"
#include <string>
#include <vector>

using namespace std;


const long SelectionCityPage::IdButtonInsert =::wxNewId();
const long SelectionCityPage::IdButtonComeBack =::wxNewId();

BEGIN_EVENT_TABLE (SelectionCityPage, wxFrame)

                EVT_BUTTON(IdButtonInsert, SelectionCityPage::InsertCity)
                EVT_BUTTON(IdButtonComeBack, SelectionCityPage::ComeBack)

END_EVENT_TABLE()

SelectionCityPage::SelectionCityPage(const wxString &title) :
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)){


    wxPanel *Mainpanel = new wxPanel(this, -1);

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);


    wxFlexGridSizer *fgs=new wxFlexGridSizer(6,2,20,5);

    City *table;

    std::vector<std::string> cities;

    cities=table->select();
    wxVector<string> choices;
    for (int k=0; k<table->number_of_city(); k++){
        choices.push_back(cities[k]);
    }
    wxString myString[table->number_of_city()];
    for (int i=0;i<table->number_of_city();i++) {
        myString[i].Append(choices[i]);
    }

    cities.clear();
    choices.clear();

    wxStaticText *City = new wxStaticText(Mainpanel, -1, wxT("City"));

    Insert=new wxButton (Mainpanel,IdButtonInsert,_T ("Insert"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton(Mainpanel,IdButtonComeBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    choiceC=new wxChoice(Mainpanel, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceC->Append("Select");
    choiceC->Append("All");
    choiceC->Append(table->number_of_city(),myString);


    fgs->Add(City,0);
    fgs->Add(choiceC,1, wxEXPAND);

    fgs->Add(Insert,0);
    fgs->Add(Back,0);



    fgs->AddGrowableRow(1, 1);
    fgs->AddGrowableCol(1, 1);




    hbox->Add(fgs, 1, wxALL, 10);



    Mainpanel->SetSizer(hbox);
    //this->SetSizer(MainBox);

    Centre();

}

void SelectionCityPage::InsertCity(wxCommandEvent &event) {
    if (choiceC->GetSelection() == wxNOT_FOUND)
    {
        wxMessageBox("Choose an option", "Error", wxICON_ERROR);
    } else {
        int Id_city = choiceC->GetSelection();
        string city = choiceC->GetString(Id_city).ToStdString();
        Close();
        UsersDataListPage *view= new UsersDataListPage(_T("USERS"), city);
        view->Show(TRUE);
    }
}

void SelectionCityPage::ComeBack(wxCommandEvent &event) {

    Close();

}
