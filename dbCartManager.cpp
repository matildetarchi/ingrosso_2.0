//
// Created by Andrea Lipperi on 15/06/23.
//

#include "dbCartManager.h"

using namespace std;

dbCartManager::dbCartManager(SQLite::Database *d) {
    db = d;
}

void dbCartManager::add_to_db() {

    //metodo per aggiungere al carrello un nuovo prodotto
    int index=cart->get_num_prod()-1;
    prod = cart->products[index];
    //prendo l'id dell'utente che sta usando il programma e
    // del fornitore del prodotto che sto mettendo nel carrello
    string query_user = "SELECT id FROM users WHERE username='"+cart->get_client()+"'";
    int id_user = db->execAndGet(query_user);

    string query_prov = "SELECT id FROM users WHERE username='"+prod->get_username_prov()+"'";
    int id_prov = db->execAndGet(query_prov);

    string query_store = "SELECT id FROM store WHERE desc_prod='"+prod->get_desc()+"' AND id_prov="+ to_string(id_prov)+"";
    int id_store = db->execAndGet(query_store);

    //inserisco i dati nel db
    string query_insert = "INSERT INTO cart (quantity, id_store,id_user, id_prov) VALUES (" + to_string(prod->get_quantity()) + ", " + to_string(id_store) + ","+ to_string(id_user)+","+to_string(id_prov)+")";

    db->exec(query_insert);

}

void dbCartManager::remove_all(const string &username) {

    //metodo per rimuovere tutti i prodotti dal carello
    // una volta effettuato l'ordine da quest'ultimo

    //prendo l'id dell'utente che sta usando il programma
    int id = user->get_db_id();

    //lancio la query di delete dal db
    string query = "DELETE FROM cart WHERE id_user = "+ to_string(id)+"";
    db->exec(query);

    //cart->remove_all();
}

void dbCartManager::remove_prod(int id_s) {

    //metodo per eliminare un solo prodotto dal carrello

    string query = "DELETE FROM cart WHERE id_store = "+ to_string(id_s)+"";
    id_s = db->exec(query);

    cart->remove_one(id_s);
}


void dbCartManager::select(const string &username) {

    //metodo per prendere i valori dei prodotti nel carrello dell'utente

    //prendo l'id dell'utente che sta usando il programma
    int id = user->get_db_id();

    //lancio la query che prende i valori dal db
    string select="SELECT desc_prod, price_product, username, quantity FROM users, cart, store WHERE id_store = store.id AND store.id_prov = users.id AND id_user="+to_string(id) +" ORDER BY username;";
    SQLite::Statement query(*db,select);

    //inserisco i valori all'interno del vettore e la restituisco

    while (query.executeStep()){

        string desc=query.getColumn(0).getText();
        double price=query.getColumn(1).getDouble();
        string username_prov=query.getColumn(2).getText();
        int quantity=query.getColumn(3).getInt();
        prod->set_desc(desc);
        prod->set_price(price);
        prod->set_quantity(quantity);
        prod->set_username_prov(username_prov);

        cart->add_product(std::move(prod));
    }

}



