//
// Created by dario on 15/06/2023.
//

#include "dbOrdersManager.h"



dbOrdersManager::dbOrdersManager(const shared_ptr<Database>& d) {
        db = d->get_db();
}



void dbOrdersManager::add_to_db(){

    std::shared_ptr<Date> d = date->get_current_date();
    std::string dataString = d->to_string("%d/%m/%Y");

    int id_client = user->get_db_id();
    string username = user->get_username();
    //lancio le query di inserimento dell'ordine
    string query_insert_ord = "INSERT INTO orders (status, date_order, id_client) VALUES ('S','"+ dataString +"', '"+
                              to_string(id_client)+"');";

    db->exec(query_insert_ord);

    //prendo id ordine inserito (sel max)
    string select_id_last_order = "SELECT MAX(id) FROM orders";

    int id_last_ord = db->execAndGet(select_id_last_order).getInt();

    shared_ptr<Cart> cart = user->get_cart();
    vector<shared_ptr<Product>> products = cart->get_products();

    for( const shared_ptr<Product>& p: products) {
        string query_insert_ord_detail = "INSERT INTO orders_details (quantity, id_order, id_product) VALUES ('"+to_string(p->get_quantity())+"', '"+ to_string(id_last_ord) +"', '"+
                                       to_string(p->get_id_store())+"');";

        db->exec(query_insert_ord_detail);
    }


    string select_last_order_products = "SELECT  desc_prod, price_product, quantity, name, id_product, available_quantity FROM users, orders, orders_details, store, subcategories WHERE orders.id = id_order AND id_product = store.id AND id_sub = subcategories.id AND id_client = '" + to_string(id_client) + "' AND id_order ='" + to_string(id_last_ord) + "'";

    SQLite::Statement query(*db, select_last_order_products);

    std::shared_ptr<Order> ord = std::make_shared<Order>(id_last_ord, "S", username);

    while (query.executeStep()) {
        // Per ogni prodotto trovato creo un oggetto prodotto e chiamo la addOrderProduct
        int q_available = query.getColumn(5).getInt();
        int id_store = query.getColumn(4).getInt();
        string subcategories = query.getColumn(3).getText();
        int quantity = query.getColumn(2).getInt();
        double price_prod = query.getColumn(1).getInt();
        string desc_prod = query.getColumn(0).getText();

        std::shared_ptr<Product> product = std::make_shared<Product>(desc_prod, price_prod, quantity,q_available, username, subcategories);// Qui passate i paraemtri che servono a OrderProduct
        product->set_id_store(id_store);
        ord->add_to_order(std::move(product));

    }

    tab_order->add_order(ord);
}

void dbOrdersManager::change_status( const string &new_status, int id_order) {

    //metodo che cambia lo status dell'ordine da sospeso(S) a approvato(A) o rifiutato(D)

    //lancio la query di modifica
    string query = "UPDATE orders SET status = '"+new_status+"' WHERE id = " + to_string(id_order) +"";
    db->exec(query);

    shared_ptr<OrdersList> order_s = user->get_order_list();
    order_s->modify_status(id_order, new_status);

}


void dbOrdersManager::select_for_provider() {
    int id_user = user->get_db_id();
    string username = user->get_username();

    string query_count="SELECT count(*) FROM store WHERE id_prov = '" + to_string(id_user) +"'";
    int count=db->execAndGet(query_count).getInt();
    if (count >0) {

        string select_id_store = "SELECT id FROM store WHERE id_prov = '" + to_string(id_user) + "'";
        int id_store = db->execAndGet(select_id_store).getInt();

        string select_orders = "SELECT orders.id, date_order, status, id_client FROM orders, orders_details, users, store WHERE orders.id = id_order AND id_product = store.id AND id_client = users.id GROUP BY date_order";
        SQLite::Statement query_ord(*db, select_orders);


        while (query_ord.executeStep()) {
            //mettere dettagli ordine da poi usare nella query dopo
            int id_order = query_ord.getColumn(0);
            string date_string = query_ord.getColumn(1).getText();
            string status = query_ord.getColumn(2).getText();
            int id_client = query_ord.getColumn(3);

            //prendo username cliente
            string select_us_cl = "SELECT username FROM users WHERE  id= '" + to_string(id_client) + "'";
            string username_client = db->execAndGet(select_us_cl);


            // trasformo la stringa data in un oggetto Date
            date = date->string_to_date_converter(date_string);

            order = make_shared<Order>(id_order, status, username_client);
            order->set_date(date);

            string select_products =
                    "SELECT desc_prod, price_product, quantity, id_sub, available_quantity FROM store, orders_details WHERE id_product = store.id AND id_order = '" +
                    to_string(id_order) + "'AND id_prov = '" + to_string(id_user) + "'";
            SQLite::Statement query_prod(*db, select_products);
            while (query_prod.executeStep()) {

                int q_available = query_prod.getColumn(4);
                int id_subcategories = query_prod.getColumn(3);
                int quantity = query_prod.getColumn(2);
                double price_prod = query_prod.getColumn(1);
                string desc_prod = query_prod.getColumn(0).getText();

                string select_sub_name =
                        "SELECT name FROM subcategories WHERE id = '" + to_string(id_subcategories) + "'";
                string sub_name = db->execAndGet(select_sub_name);

                std::shared_ptr<Product> product = std::make_shared<Product>(desc_prod, price_prod, quantity,
                                                                             q_available, username, sub_name);
                product->set_id_store(id_store);
                order->add_to_order(product);

            }

            tab_order->add_order(order);

        }
    }
}

void dbOrdersManager::select_for_client() {

    int id_user = user->get_db_id();
    string username = user->get_username();

    string query_count = "SELECT count(*) FROM orders WHERE id_client = '" + to_string(id_user) + "'";
    int count = db->execAndGet(query_count).getInt();

    if (count > 0) {
        string select_orders =
                "SELECT orders.id, date_order, status FROM orders WHERE id_client = '" + to_string(id_user) + "'";
        SQLite::Statement query_ord(*db, select_orders);


        while (query_ord.executeStep()) {
            //mettere dettagli ordine da poi usare nella query dopo
            int id_order = query_ord.getColumn(0).getInt();
            string date_string = query_ord.getColumn(1).getText();
            string status = query_ord.getColumn(2).getText();

            // trasformo la stringa data in un oggetto Date
            date = date->string_to_date_converter(date_string);

            shared_ptr<Order> o = make_shared<Order>(id_order, status, username);
            o->set_date(date);


            string select_products =
                    "SELECT desc_prod, price_product, quantity, id_sub, id_product, available_quantity FROM store, orders_details, orders WHERE id_product = store.id AND orders_details.id_order = '" +
                    to_string(id_order) + "'AND id_client = '" + to_string(id_user) + "'";
            SQLite::Statement query_prod(*db, select_products);

            while (query_prod.executeStep()) {

                int q_available = query_prod.getColumn(5);
                int id_subcategories = query_prod.getColumn(3);
                int quantity = query_prod.getColumn(2);
                double price_prod = query_prod.getColumn(1);
                string desc_prod = query_prod.getColumn(0).getText();
                int id_store = query_prod.getColumn(4);

                string select_sub_name =
                        "SELECT name FROM subcategories WHERE id = '" + to_string(id_subcategories) + "'";
                string sub_name = db->execAndGet(select_sub_name);

                std::shared_ptr<Product> product = std::make_shared<Product>(desc_prod, price_prod, quantity,
                                                                             q_available, username, sub_name);
                product->set_id_store(id_store);
                o->add_to_order(std::move(product));

            }

            tab_order->add_order(o);
        }
        user->set_order_list(tab_order);
    }
}

void dbOrdersManager::cancel_order(int id_order) {

    //metodo che permette a un utente di annullare il proprio ordine, selezionandolo tra quelli fatti

    //prendo l'id dell'utente che sta usando il programma
    int id = user->get_db_id();

    //lancio la query delete
    string query_cancel_details = "DELETE FROM orders_details WHERE id_order = '" + to_string(id_order) + "'";
    db->exec(query_cancel_details);

    string query_cancel = "DELETE FROM orders WHERE id = '" + to_string(id_order) + "' AND id_client ='" +
                to_string(id) + "'";
    db->exec(query_cancel);

    tab_order->remove_one(id_order);

}


int dbOrdersManager::select_count_for_provider(){
    if(user->get_type()== "F") {
        tab_order=user->get_order_list();
        int count =tab_order->get_num_order();
        return count;
    }else
        throw std::runtime_error("Errore, l'utente selezionato non è un fornitore");

}

int dbOrdersManager::select_count_for_client(int control){
    if(user->get_type()== "C") {
        int count = 0;
        tab_order = user->get_order_list();
        if (control == 0){
            vector<shared_ptr<Order>> o_l = tab_order->get_orders();
            int i = 0;
            while(i < o_l.size()){
                if(o_l[i]->get_status() == "S"){
                    count ++;
                    i++;
                }
                i++;
            }
        }else {
            count = tab_order->get_num_order();
        }
        return count;
    }
    else
        throw std::runtime_error("Errore, l'utente selezionato non è un cliente");

}