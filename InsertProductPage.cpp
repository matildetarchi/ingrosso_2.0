//
// Created by dario on 05/12/2022.
//

#include "InsertProductPage.h"
#include "GlobalVariables.h"
#include "subcategories.h"
#include "categories.h"
#include "store.h"
#include <vector>
#include <wx/spinctrl.h>


const long InsertProductPage::IdButtonInsert =::wxNewId();
const long InsertProductPage::IdButtonComeBack =::wxNewId();

BEGIN_EVENT_TABLE (InsertProductPage, wxFrame)

                EVT_BUTTON(IdButtonInsert, InsertProductPage::InsertProduct)
                EVT_BUTTON(IdButtonComeBack, InsertProductPage::ComeBack)

END_EVENT_TABLE()

InsertProductPage::InsertProductPage(const wxString &title) :
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 400)){

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

    wxStaticText *Category = new wxStaticText(this, -1, wxT("Category"));
    wxStaticText *SubCategory = new wxStaticText(this, -1, wxT("Subcategory"));
    wxStaticText *Name = new wxStaticText(this, -1, wxT("Product's name"));
    wxStaticText *Qty_avb= new wxStaticText(this, -1, wxT("Quantity available"));
    wxStaticText *Cost= new wxStaticText(this, -1, wxT("Price €"));

    Insert=new wxButton (this,IdButtonInsert,_T ("Insert"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton(this,IdButtonComeBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    choiceC=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceC->Append("Select");
    choiceC->Append(table_cat->number_of_cat(),myString);

    choiceC->Bind(wxEVT_CHOICE, &InsertProductPage::OnChoice, this);

    choiceSubC=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    choiceSubC->Append("Select");
    tcQ = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);



    tcName = new wxTextCtrl(this, -1);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(Category, 0, wxALL, 5);
    sizer->Add(choiceC, 0, wxALL, 5);
    sizer->Add(SubCategory, 1, wxEXPAND | wxALL, 5);
    sizer->Add(choiceSubC, 0, wxALL, 5);
    sizer->Add(Name, 1, wxEXPAND | wxALL, 5);
    sizer->Add(tcName, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Qty_avb, 1, wxEXPAND | wxALL, 5);
    sizer->Add(tcQ, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(Cost, 1, wxEXPAND | wxALL, 5);
    tcC = new wxSpinCtrlDouble(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 500, 0, 0.01);
    sizer->Add(tcC, 0, wxALL, 5);
    sizer->Add(Insert, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Back, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();

}
void InsertProductPage::OnChoice(wxCommandEvent& event) {
    choiceSubC->Clear();
    choiceSubC->Append("Select");
    wxVector<string> choices2;
    Subcategories sub;
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
}
void InsertProductPage::InsertProduct(wxCommandEvent &event) {

    if (choiceC->GetSelection() == wxNOT_FOUND || choiceSubC->GetSelection() < 1 || tcName->IsEmpty() || tcQ->GetValue()==0||
        tcC->GetValue()==0.00) {
        wxMessageBox("Inset Every Value", "Error", wxICON_ERROR);
    } else {
        int Id_subcategory = choiceSubC->GetSelection();
        std::string Sub_category = choiceSubC->GetString(Id_subcategory).ToStdString();
        int Id_category = choiceC->GetSelection();
        std::string Category = choiceC->GetString(Id_category).ToStdString();
        std::string Name = tcName->GetValue().ToStdString();
        int Quantity = tcQ->GetValue();
        double Price = tcC->GetValue();
        std::string username = GlobalVariables::GetInstance().GetValueUsername();
        StoreProduct *store = new StoreProduct(Quantity, Sub_category, Price, Name, username);
        store->add();
    }
}
void InsertProductPage::ComeBack(wxCommandEvent &event) {

    Close();

}