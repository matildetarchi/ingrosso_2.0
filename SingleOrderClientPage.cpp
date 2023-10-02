//
// Created by Andrea Lipperi on 04/05/23.
//

#include "SingleOrderClientPage.h"


const long SingleOrderClientPage::IdButtonBack =::wxNewId();


BEGIN_EVENT_TABLE (SingleOrderClientPage, wxDialog)
                EVT_BUTTON(IdButtonBack, SingleOrderClientPage::ComeBack)
END_EVENT_TABLE()

SingleOrderClientPage::SingleOrderClientPage(Engine *e, const wxString &title, int code_order): engine(e), id_order(code_order),
        wxDialog(nullptr, -1, title, wxPoint(-1, -1), wxSize(500, 350)) {


    client = engine->get_client();
    shared_ptr<Database> db;
    db = engine->get_db();
    shared_ptr<SQLite::Database> database;
    database = db->get_db();
    orders_list = client->get_order_list();
    orders = orders_list->get_orders();


    int i = 0;
    while (i < orders.size()) {
        if(orders[i]->get_id() == id_order)
            break;
        i++;
    }

    order = orders[i];
    order_p = order->get_order_prod();
    string sel_count = "SELECT COUNT (*) FROM orders, orders_details WHERE orders.id = id_order AND id_order = "+
                       to_string(id_order)+"";
    int row = database->execAndGet(sel_count);

    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(row+1, 4);
    grid->SetColLabelValue(1, "Quantity Requested");
    grid->SetColLabelValue(2, "Provider");
    grid->SetColLabelValue(3, "Total Price");
    grid->SetColLabelValue(0, "Product");

    double t_p = order->get_total(order);
    string total_price = (to_string(t_p));

    for ( i = 0; i < row; i++) {
        int q = order_p[i]->get_quantity();
        string quantity = (to_string(q));
        int id_prod = order_p[i]->get_id_store();
        string query_us_prov = "SELECT username FROM users, store WHERE store.id = "+to_string(id_prod)+" AND users.id = id_prov";
        string us_prov = database->execAndGet(query_us_prov);
        string desc = order_p[i]->get_desc();

        grid->SetReadOnly(i, 0, true);
        grid->SetCellValue(i, 0, desc);
        grid->SetReadOnly(i, 1, true);
        grid->SetCellValue(i, 1, quantity);
        grid->SetReadOnly(i, 2, true);
        grid->SetCellValue(i, 2, us_prov);

    }
    grid->SetReadOnly(row, 3, true);
    grid->SetCellValue(row,3, total_price );

    grid->SetSelectionMode(wxGrid::wxGridSelectRows);
    grid->AutoSize();


    Back = new wxButton(this, IdButtonBack, _T ("Back"), wxDefaultPosition, wxDefaultSize, 0);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(grid, 1, wxALL, 5);

    sizer->Add(Back, 1,  wxALL, 5);
    SetSizer(sizer);

    Centre();
}

void SingleOrderClientPage::ComeBack(wxCommandEvent &event) {
    Close();
}
