//
// Created by Andrea Lipperi on 15/06/23.
//

#include "dbCartManager.h"



using namespace std;

dbCartManager::dbCartManager(const shared_ptr<Database>& d) {
    db = d->get_db();

}

void dbCartManager::add_to_db() {

    //metodo per aggiungere al carrello un nuovo prodotto
    int index = cart->get_num_prod()-1;

    prod_list = cart->get_products();
    prod = prod_list[index];

    //prendo l'id dell'utente che sta usando il programma e
    // del fornitore del prodotto che sto mettendo nel carrello
    string query_user = "SELECT id FROM users WHERE username='"+cart->get_client()+"'";
    int id_user = db->execAndGet(query_user);

    string query_prov = "SELECT id FROM users WHERE username='"+prod->get_username_prov()+"'";
    int id_prov = db->execAndGet(query_prov);

    string query_store = "SELECT id FROM store WHERE desc_prod='"+prod->get_desc()+"' AND id_prov = '"+ to_string(id_prov)+"'";
    int id_store = db->execAndGet(query_store);

    //inserisco i dati nel db
    string query_insert = "INSERT INTO cart (quantity, id_store,id_user, id_prov) VALUES ('" + to_string(prod->get_quantity()) + "', '" + to_string(id_store) + "', '"+ to_string(id_user)+"', '"+to_string(id_prov)+"')";

    db->exec(query_insert);

}

void dbCartManager::remove_all() {

    //metodo per rimuovere tutti i prodotti dal carello

    //prendo l'id dell'utente che sta usando il programma
    int id = client->get_db_id();

    //lancio la query di delete dal db
    string query = "DELETE FROM cart WHERE id_user = '"+ to_string(id)+"'";
    db->exec(query);

    cart->remove_all();
}

void dbCartManager::remove_prod(int id_s) {

    //metodo per eliminare un solo prodotto dal carrello

    string query = "DELETE FROM cart WHERE id_store = '"+ to_string(id_s)+"'";
    id_s = db->exec(query);

    cart->remove_one(id_s);
}


void dbCartManager::select() {

    //metodo per prendere i valori dei prodotti nel carrello dell'utente

    //prendo l'id dell'utente che sta usando il programma
    int id = client->get_db_id();
    string us_client= client->get_username();
    string query_count="SELECT count(*) FROM users, cart, store WHERE id_store = store.id AND store.id_prov = users.id AND id_user ='"+to_string(id) +"'";
    int count = db->execAndGet(query_count).getInt();


    if (count>0) {
        //lancio la query che prende i valori dal db
        string select = "SELECT desc_prod, price_product, username, quantity, available_quantity, id_sub, store.id FROM users, cart, store WHERE id_store = store.id AND store.id_prov = users.id AND id_user ='" +
                to_string(id) + "' ORDER BY username;";
        SQLite::Statement query(*db, select);

        //inserisco i valori all'interno del vettore e la restituisco

        while (query.executeStep()) {

            string desc = query.getColumn(0).getText();
            double price = query.getColumn(1).getDouble();
            string username_prov = query.getColumn(2).getText();
            int quantity = query.getColumn(3);
            int available_q = query.getColumn(4);
            int id_sub = query.getColumn(5);
            int id_store = query.getColumn(6);

            string select_sub_name = "SELECT name FROM subcategories WHERE id = '" + to_string(id_sub) + "'";
            string sub_name = db->execAndGet(select_sub_name).getString();


            shared_ptr<Product> product = make_shared<Product>(desc, price, quantity, available_q, username_prov, sub_name);
            product->set_id_store(id_store);

            cart->add_product(product);
        }
    }
}

int dbCartManager::select_count_of_prod(){
    //seleziono l'id del cliente che sta usando il programma
    int id_client = client->get_db_id();

    //prendo la quantità di prodotti presenti
    string query_select_count = "SELECT count(*) FROM cart WHERE id_user ='" + to_string(id_client) + "'";
    int count = db->execAndGet(query_select_count).getInt();
    return count;
}

bool dbCartManager::control_if_exist(const shared_ptr<Product>& p) {
    string select_prod = "SELECT count(*) FROM store, cart WHERE id_store = store.id AND id_user = '"+ to_string(client->get_db_id()) +"' AND desc_prod = '" + p->get_desc() + "'";
    int count = db->execAndGet(select_prod);
    if(count > 0)
        return true;
    else
        return false;
}

int dbCartManager::select_id_cart(const string &desc, const string &prov) {
    string select_id_prov = "SELECT id FROM users WHERE username = '"+prov+"'";
    int id_prov = db->execAndGet(select_id_prov);
    string select_id_cart = "SELECT cart.id FROM cart, store WHERE store.id = id_store AND cart.id_prov = "+ to_string(id_prov)+" AND desc_prod = '"+desc+"' AND id_user = "+
                                                                                                                                                    to_string(client->get_db_id())+"";
    int id_cart = db->execAndGet(select_id_cart);
    return id_cart;
}

void dbCartManager::change_quantity(int id, int quantity) {
    string update = "UPDATE cart SET quantity = "+ to_string(quantity)+" WHERE id = "+ to_string(id)+"";
    db->exec(update);
}


