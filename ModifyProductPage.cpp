//
// Created by Andrea Lipperi on 31/03/23.
//

#include "ModifyProductPage.h"



const long ModifyProductPage::IdButtonConfirm =::wxNewId();

BEGIN_EVENT_TABLE (ModifyProductPage, wxDialog)
                EVT_BUTTON(IdButtonConfirm, ModifyProductPage::OnConfirm)
END_EVENT_TABLE()

ModifyProductPage::ModifyProductPage(Engine *e, const wxString &title, int id_store):engine(e), id(id_store),
                   wxDialog(nullptr, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {

    prov = engine->get_prov();

    auto *desc = new wxStaticText(this, -1, wxT("Name Product"));
    auto *price = new wxStaticText(this, -1, wxT("Price"));
    auto *quant = new wxStaticText(this, -1, wxT("Available Quantity"));

    Confirm=new wxButton (this,IdButtonConfirm,_T ("Confirm"),wxDefaultPosition,wxDefaultSize,0);
    db_store= engine->get_db_store();

    prod = db_store->select_prod_to_modify(id);
    tcD = new wxTextCtrl(this, wxID_ANY,prod->get_desc());

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(desc);
    sizer->Add(tcD, 0, wxALL, 5);
    sizer->Add(price);
    tcP = new wxSpinCtrlDouble(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, prod->get_price(), 0.01);
    sizer->Add(tcP, 0, wxALL, 5);
    sizer->Add(quant);
    tcQ = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, prod->get_q_available());
    sizer->Add(tcQ, 0, wxALL, 5);
    sizer->Add(Confirm,0);


    SetSizer(sizer);

    Centre();
}


void ModifyProductPage::OnConfirm(wxCommandEvent &event) {
    Close();

    std::string new_desc=tcD->GetValue().ToStdString();
    double new_price = tcP->GetValue();
    int new_available_quant= tcQ->GetValue();
    db_store->change_data(id, new_desc, new_price, new_available_quant);

    prov->modify_prod(id, new_desc, new_price, new_available_quant);
}