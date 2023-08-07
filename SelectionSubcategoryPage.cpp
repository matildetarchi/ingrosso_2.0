//
// Created by dario on 05/12/2022.
//
/*
#include "SelectionSubcategoryPage.h"
#include "dbCategoriesManager.h"
#include "dbSubcategoriesManager.h"
#include "ProductListPage.h"
#include <string>
#include <vector>

using namespace std;


const long SelectionSubcategoryPage::IdButtonInsert =::wxNewId();
const long SelectionSubcategoryPage::IdButtonComeBack =::wxNewId();

BEGIN_EVENT_TABLE (SelectionSubcategoryPage, wxFrame)

                EVT_BUTTON(IdButtonInsert, SelectionSubcategoryPage::InsertProduct)
                EVT_BUTTON(IdButtonComeBack, SelectionSubcategoryPage::ComeBack)

END_EVENT_TABLE()

SelectionSubcategoryPage::SelectionSubcategoryPage(const wxString &title) :
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)){


    wxPanel *Mainpanel = new wxPanel(this, -1);

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);


    wxFlexGridSizer *fgs=new wxFlexGridSizer(6,2,20,5);

    Categories *table_cat;

    std::vector<std::string> categories;

    categories=table_cat->select();
    wxVector<string> choices;
    for (int k=0; k<table_cat->number_of_cat(); k++){
        choices.push_back(categories[k]);
    }
    wxString myString[table_cat->number_of_cat()];
    for (int i=0;i<table_cat->number_of_cat();i++) {
        myString[i].Append(choices[i]);
    }

    categories.clear();
    choices.clear();

    wxStaticText *Category = new wxStaticText(Mainpanel, -1, wxT("Category"));
    wxStaticText *SubCategory = new wxStaticText(Mainpanel, -1, wxT("Subcategory"));
    wxStaticText *Disp = new wxStaticText(Mainpanel, -1, wxT("Disponibility"));

    Insert=new wxButton (Mainpanel,IdButtonInsert,_T ("Insert"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton(Mainpanel,IdButtonComeBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    choiceC=new wxChoice(Mainpanel, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceC->Append("Select");
    choiceC->Append(table_cat->number_of_cat(),myString);

    choiceC->Bind(wxEVT_CHOICE, &SelectionSubcategoryPage::OnChoice, this);

    choiceSubC=new wxChoice(Mainpanel, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    wxString myDisp[]={"Only Available", "All"};
    choiceDisp=new wxChoice(Mainpanel, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceDisp->Append("Select");
    choiceDisp->Append(2,myDisp);

    fgs->Add(Category,0);
    fgs->Add(choiceC,1, wxEXPAND);
    fgs->Add(SubCategory,0);
    fgs->Add(choiceSubC,1, wxEXPAND);
    fgs->Add(Disp,0);
    fgs->Add(choiceDisp,1, wxEXPAND);

    fgs->Add(Insert,0);
    fgs->Add(Back,0);



    fgs->AddGrowableRow(1, 1);
    fgs->AddGrowableCol(1, 1);




    hbox->Add(fgs, 1, wxALL, 10);



    Mainpanel->SetSizer(hbox);
    //this->SetSizer(MainBox);

    Centre();

}
void SelectionSubcategoryPage::OnChoice(wxCommandEvent& event) {
    choiceSubC->Clear();
    choiceSubC->Append("Select");
    wxVector<string> choices2;
    dbSubcategoriesManager sub;
    std::vector<std::string> subcategories;
    string cat=event.GetString().ToStdString();
    subcategories = sub.select(cat);
    for (int k=0; k<subcategories.size(); k++){
        choices2.push_back(subcategories[k]);
    }
    wxString myString[choices2.size()];
    for (int i=0;i<choices2.size();i++) {
        myString[i].Append(choices2[i]);
    }
    choiceSubC->Append(subcategories.size(), myString);
    subcategories.clear();
    choices2.clear();
    myString->clear();
}
void SelectionSubcategoryPage::InsertProduct(wxCommandEvent &event) {
    if (choiceC->GetSelection() == wxNOT_FOUND || choiceSubC->GetSelection() < 1 || choiceDisp->GetSelection() == wxNOT_FOUND)
    {
        wxMessageBox("Choose an option", "Error", wxICON_ERROR);
    } else {
        int Id_subcategory = choiceSubC->GetSelection();
        int Id_disp = choiceDisp->GetSelection();
        string sub_name = choiceSubC->GetString(Id_subcategory).ToStdString();
        string disp = choiceDisp->GetString(Id_disp).ToStdString();
        ProductListPage *prodList = new ProductListPage(_T("ALL PRODUCT"), sub_name, disp);
        prodList->Show(TRUE);
    }
}

void SelectionSubcategoryPage::ComeBack(wxCommandEvent &event) {

    Close();

}
 */