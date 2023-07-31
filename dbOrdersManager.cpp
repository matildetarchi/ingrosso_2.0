//
// Created by dario on 15/06/2023.
//
#define only_pending 0
#include "dbOrdersManager.h"

dbOrdersManager::dbOrdersManager(SQLite::Database* d) {
        db=d;
}

void dbOrdersManager::add_to_db() {

    //metodo che aggiunge un ordine al database
    int index= tab_order->get_num_prod()-1;
    vector<shared_ptr<OrdersList>> orders = tab_order->get_orders();
    order = orders[index];

    string query_cust="SELECT id FROM users WHERE username='"+order->get_us_client()+"'";
    int id_cust=db->execAndGet(query_cust);

   // cast per convertire l'oggetto data in una stringa
    Date* data= order->get_date();
    std::stringstream ss;
    ss << data;
    std::string dataString = ss.str();

    //lancio le query che inseriscono l'ordine
    string query_insert_ord="INSERT INTO orders (status, date_order,id_client) VALUES ('S','"+ dataString +"', "+
                        to_string(id_cust)+");";

    db->exec(query_insert_ord);

    for(int i = 0; i<order->get_num_prod(); i++) {

        //seleziono i valori id dei fornitori a cui sarà inviato l'ordine
        prod = order->get_prod(i);
        string query_prov="SELECT id FROM users WHERE username='"+prod->get_username_prov()+"'";
        int id_provider = db->execAndGet(query_prov);
        string query_id_store = "SELECT id FROM store WHERE id_prov = 'id_provider'";
        int id_store = db->execAndGet(query_id_store);
        //**************order->get_id()
        string query_insert_ord_detail="INSERT INTO orders_details (quantity, id_order, id_product) VALUES ('"+to_string(prod->get_quantity())+"'"+ to_string(order->get_id()) +"', "+
                                       to_string(id_store)+");";

        db->exec(query_insert_ord_detail);
    }

}

void dbOrdersManager::changeStatus(const string &username, const string &new_status) {

    //metodo che cambia lo status dell'ordine da sospeso(S) a approvato(A) o rifiutato(D)

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db->execAndGet(query_user).getInt();

    //lancio la query di modifica
    string query = "UPDATE orders SET status = '"+new_status+"' WHERE id = " + to_string(da interfaccia) + ";";
    db->exec(query);

    order->set_status(id, new_status);

}


void dbOrdersManager::select_for_provider(const string &username) {

    string query_user="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db->execAndGet(query_user).getInt();

    string select_id_store = "SELECT id FROM store WHERE id_prov=" + to_string(id) + "";
    int id_store = db->execAndGet(query_user).getInt();

    (SQLite::Statement(*db, select_id_store));
    //deve fare il ciclo su id_store, quindi finche non sono finiti gli id_store continua a controllare quali sono uguali
    while (query.executeStep()) {
        string select_products = "SELECT desc_prod, quantity, status, date_order FROM orders, orders_details, store WHERE id_order = orders.id AND id_product =" + to_string(id_store) + "";
    }

    //prendo il valore dell'id dell'utente che sta usando il programma
    string query_id_user = "SELECT id FROM users WHERE username ='" + username + "'";
    int id_us = db->execAndGet(query_id_user).getInt();

    //controllo di quali tipo di ordini si vuole sapere i dati
    //only_pending=0 solo in sospeso
    //poi quindi creo le colonne della matrice
    //lancio la query e popolo la matrice per poi lanciarla
    string select =
            "SELECT username, date_order, status FROM users, orders, store WHERE id_client = users.id AND id_store = store.id AND id_prov=" +
            to_string(id_us) + "";

    SQLite::Statement query(*db, select);

    while (query.executeStep()) {
        int id_sing_order = query.getColumn(0).getInt();
        string username_cust = query.getColumn(1).getText();
        Date *date_order = (Date *) query.getColumn(2).getText();
        string status = query.getColumn(3).getText();
        string desc_prod = query.getColumn(4).getText();

        tab_order->add_order(status, date_order, username_cust, id_sing_order);
    }
    // Prendo il vector con gli Order che ho appena messo in tab_order
    vector<Order *> orders = tab_order->get_orders();
    // Ciclo su tutti gli elementi in orders e per ognuno di questi
    // faccio una query al databse per prendere i prodotti relativi a quell'ordine
    for (Order *ord: orders) {
        //sarebbe che while sto analizzando il solito ordine e quindi con il solito id chiave, faccio quello che c'è dentro
        string query_order = "SELECT id FROM orders WHERE non lo soooo**** ='" + username + "'";
        int id_gen_ord = db->execAndGet(query_user).getInt();
        int id_ord_db = ord->get_id_s_prod();
        string select =
                "SELECT  desc_prod, price_product, quantity, name, store.id FROM users, orders, store,subcategories WHERE id_cust=users.id AND id_prov=" +
                to_string(id) + " AND id =" + to_string(id_gen_ord) + ""; //dovrebbe essere id_ordine = id che hopreso prima per fare il ciclo

        SQLite::Statement query(*db, select);

        while (query.executeStep()) {
            // Per ogni prodotto trovato creo un oggetto prodotto e chiamo la addOrderProduct
            int id_store = query.getColumn(4).getInt();
            string subcategories = query.getColumn(3).getText();
            int quantity = query.getColumn(2).getInt();
            int price_prod = query.getColumn(1).getInt();
            string desc_prod = query.getColumn(0).getText();

            std::unique_ptr<Product *> product = std::make_unique<Product *>();// Qui passate i paraemtri che servono a OrderProduct
            *product = new Product(desc_prod, price_prod, quantity, username, subcategories, id_store);

            ord->add_order(std::move(product));
            //qui finisce il ciclo che ho iniziato sopra

        }

    }
}


    void dbOrdersManager::select_for_client(const string &username) {

        //matodo che prende i dati generali degli ordini di un cliente

        //prendo il valore dell'id dell'utente che sta usando il programma
        string query_user = "SELECT id FROM users WHERE username ='" + username + "'";
        int id = db->execAndGet(query_user).getInt();

        string select =
                "SELECT id_single_order, username, date_order, status, FROM users, orders, store WHERE id_prov=users.id AND id_store=store.id AND id_cust=" +
                to_string(id) + "";

        SQLite::Statement query(*db, select);

        while (query.executeStep()) {
            int id_sing_order = query.getColumn(0).getInt();
            string username_prov = query.getColumn(1).getText();
            Date *date_order = (Date *) query.getColumn(2).getText();
            string status = query.getColumn(3).getText();

            tab_order->add_order(status, date_order, username_prov, id_sing_order);

        }
        // Prendo il vector con gli Order che ho appena messo in tab_order
        vector<Order *> orders = tab_order->get_orders();
        // Ciclo su tutti gli elementi in orders e per ognuno di questi
        // faccio una query al databse per prendere i prodotti relativi a quell'ordine
        for (Order *ord: orders) {
            int id_ord_db = ord->get_id_s_prod();

            string select = "SELECT  desc_prod, price_product, quantity, name, store.id FROM users, orders, store, subcategories WHERE  id_cust=" +

                    to_string(id) + " AND id_single_order=" + to_string(id_ord_db) + "";

            SQLite::Statement query(*db, select);
            while (query.executeStep()) {
                // Per ogni prodotto trovato creo un oggetto prodotto e chiamo la addOrderProduct
                int id_store = query.getColumn(4).getInt();
                string subcategories = query.getColumn(3).getText();
                int quantity = query.getColumn(2).getInt();
                int price_prod = query.getColumn(1).getInt();
                string desc_prod = query.getColumn(0).getText();

                std::unique_ptr<Product *> product = std::make_unique<Product *>();// Qui passate i paraemtri che servono a OrderProduct
                *product = new Product(desc_prod, price_prod, quantity, username, subcategories, id_store);

                ord->add_to_order(std::move(product));

            }



    void dbOrdersManager::cancel_order(const string &username, int id_single_order, const string &us_prov) {

        //metodo che permette a un utente di annullare il proprio ordine

        //prendo l'id dell'utente che sta usando il programma
        string query_user = "SELECT id FROM users WHERE username ='" + username + "'";
        int id = db->execAndGet(query_user).getInt();

        //prendo l'id del fornitore al quale è stato inviato l'ordine
        string query_prov = "SELECT id FROM users WHERE username ='" + us_prov + "'";
        int id_prov = db->execAndGet(query_prov).getInt();

        //lancio la query delete

        string query_cancel =
                "DELETE FROM orders WHERE id_single_order=" + to_string(id_single_order) + " AND id_cust=" +
                to_string(id) + " AND id_prov=" + to_string(id_prov) + "";
        db->exec(query_cancel);

        tab_order->remove_one(id_single_order);

    }

    int dbOrdersManager::select_id_last_order(const string &username_prov) {
        //metodo per ottenere il codice dell'ultimo ordine fatto a un fornitore

        //prendo l'id del fornitore
        string query_user = "SELECT id FROM users WHERE username ='" + username_prov + "'";
        int id_prov = db->execAndGet(query_user).getInt();

        //lancio la select del MAX(id) e ritorno il risultato
        string query_id = "SELECT MAX(id_single_order) FROM orders WHERE id_prov=" + to_string(id_prov) + "";
        int id_single_order = db->execAndGet(query_id).getInt();

        return id_single_order;

    }



        }
    }