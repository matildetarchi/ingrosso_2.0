//
// Created by Andrea Lipperi on 04/05/23.
//

#include "SingleOrderClientPage.h"


const long SingleOrderClientPage::IdButtonBack =::wxNewId();


BEGIN_EVENT_TABLE (SingleOrderClientPage, wxDialog)
                EVT_BUTTON(IdButtonBack, SingleOrderClientPage::ComeBack)

END_EVENT_TABLE()

SingleOrderClientPage::SingleOrderClientPage(Engine *e, const wxString &title, const std::string &code_order, const std::string &us_prov): engine(e), id_order(code_order), u_prov(us_prov),
        wxDialog(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {


    user= engine->get_user();
    username= user->get_username();
    db_order = engine->get_db_order();

    db_order->select_for_client();
    orders_list= user->get_order_list();
    orders= orders_list->get_orders();


    int i = 0;
    while(orders[i]->get_id()==id_order){
        i++;
    }
    order = orders[i];
    order_p = order->get_order_prod();
    int row=order->get_num_prod();

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row+1, 3);
    grid->SetColLabelValue(1, "Quantity Requested");
    grid->SetColLabelValue(2, "Total Price");
    grid->SetColLabelValue(0, "Product");

    double t_p= order->get_total(order);
    string total_price(to_string(t_p));

    for ( i = 0; i < row; i++) {
        int q= order_p[i]->get_quantity();
        string quantity(to_string(q));
        string desc= order_p[i]->get_desc();

        grid->SetReadOnly(i, 0, true);
        grid->SetCellValue(i, 0, desc);
        grid->SetReadOnly(i, 1, true);
        grid->SetCellValue(i, 1, quantity);

    }
    grid->SetCellValue(row+1,2, total_price );
    grid->AutoSize();


    Back = new wxButton(this, IdButtonBack, _T ("Back"), wxDefaultPosition, wxDefaultSize, 0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);

    sizer->Add(Back, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    Centre();
}

void SingleOrderClientPage::ComeBack(wxCommandEvent &event) {

    Close();

}
