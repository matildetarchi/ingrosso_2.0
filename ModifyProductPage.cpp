//
// Created by Andrea Lipperi on 31/03/23.
//
/*
#include "ModifyProductPage.h"




const long ModifyProductPage::IdButtonConfirm =::wxNewId();

BEGIN_EVENT_TABLE (ModifyProductPage, wxDialog)
                EVT_BUTTON(IdButtonConfirm, ModifyProductPage::OnConfirm)
END_EVENT_TABLE()

ModifyProductPage::ModifyProductPage(Engine *e, const wxString &title, int id_store):engine(e), id(id_store),
        wxDialog(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {


    wxStaticText *desc = new wxStaticText(this, -1, wxT("Name Product"));
    wxStaticText *price = new wxStaticText(this, -1, wxT("Price"));
    wxStaticText *quant = new wxStaticText(this, -1, wxT("Available Quantity"));

    Confirm=new wxButton (this,IdButtonConfirm,_T ("Confirm"),wxDefaultPosition,wxDefaultSize,0);


    data_store=store.select_to_modify(id);
    tcD = new wxTextCtrl(this, wxID_ANY,data_store[0]);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(desc);
    sizer->Add(tcD, 0, wxALL, 5);
    sizer->Add(price);
    tcP = new wxSpinCtrlDouble(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, stod(data_store[1]), 0.01);
    sizer->Add(tcP, 0, wxALL, 5);
    sizer->Add(quant);
    tcQ = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, stoi(data_store[2]));
    sizer->Add(tcQ, 0, wxALL, 5);
    sizer->Add(Confirm,0);


    SetSizer(sizer);

    Centre();
}


void ModifyProductPage::OnConfirm(wxCommandEvent &event) {
    Close();

    std::string new_desc=tcD->GetValue().ToStdString();
    double new_price = tcP->GetValue();
    int new_quant= tcQ->GetValue();
    db_store.change_data(id, new_desc, new_price, new_quant);

}
*/