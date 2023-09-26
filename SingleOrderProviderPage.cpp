//
// Created by dario on 20/04/2023.
//

#include "SingleOrderProviderPage.h"


const long SingleOrderProviderPage::IdButtonBack =::wxNewId();

BEGIN_EVENT_TABLE (SingleOrderProviderPage, wxDialog)
                EVT_BUTTON(IdButtonBack, SingleOrderProviderPage::ComeBack)
END_EVENT_TABLE()

SingleOrderProviderPage::SingleOrderProviderPage( Engine *e, const wxString &title, const std::string &code_order): engine(e), id_order(code_order),
        wxDialog(nullptr, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {

    prov = engine->get_prov();


    orders_list= prov->get_order_list();
    orders= orders_list->get_orders();


    int i = 0;
    while(orders[i]->get_id()==id_order){
        i++;
    }
    order = orders[i];
    order_p = order->get_order_prod();
    int row=order->get_num_prod();

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row+1, 4);
    grid->SetColLabelValue(0, "Product");
    grid->SetColLabelValue(1, "Quantity Requested");
    grid->SetColLabelValue(2, "Quantity Available In Store");
    grid->SetColLabelValue(3, "Total Price");

    double t_p= order->get_total(order);
    string total_price = to_string(t_p);

    for ( i = 0; i < row; i++) {
        int q= order_p[i]->get_quantity();
        string quantity(to_string(q));
        int a_q= order_p[i]->get_q_available();
        string available_q(to_string(a_q));
        string desc= order_p[i]->get_desc();

        grid->SetReadOnly(i, 0, true);
        grid->SetCellValue(i, 0, desc);
        grid->SetReadOnly(i, 1, true);
        grid->SetCellValue(i, 1, quantity);
        grid->SetReadOnly(i, 2, true);
        grid->SetCellValue(i, 2, available_q);
    }
    grid->SetCellValue(i,3, total_price);
    grid->AutoSize();


    Back = new wxButton(this, IdButtonBack, _T ("Back"), wxDefaultPosition, wxDefaultSize, 0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(grid, 1,  wxALL, 5);

    sizer->Add(Back, 1, wxALL, 5);
    SetSizer(sizer);

    Centre();
}

void SingleOrderProviderPage::ComeBack(wxCommandEvent &event) {
    Close();
}
