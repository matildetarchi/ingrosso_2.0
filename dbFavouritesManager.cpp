//
// Created by Andrea Lipperi on 15/06/23.
//

#include "dbFavouritesManager.h"

#include <utility>

dbFavouritesManager::dbFavouritesManager(shared_ptr<Database> d) {
    db = d->get_db();
    prod=make_shared<Product>();
}

void dbFavouritesManager::add_to_db() {

    //metodo che aggiunge un prodotto alla lista dei favourites
    int index = fav->get_num_prod()-1;
    vector<std::shared_ptr<Product>> prod_list;
    prod_list = fav->get_products();
    prod = prod_list[index];
    //prendo da db i valori di id dell'utente che sta usando il programma
    // e del fornitore del prodotto da inserire
    string query_cust = "SELECT id FROM users WHERE username='"+fav->get_client()+"'";
    int id_client = db->execAndGet(query_cust).getInt();

    string query_prov = "SELECT id FROM users WHERE username='"+prod->get_username_prov()+"'";
    int id_prov = db->execAndGet(query_prov).getInt();

    string query_store = "SELECT id FROM store WHERE desc_prod='"+prod->get_desc()+"' AND id_prov ='"+ to_string(id_prov)+"'";
    int id_store = db->execAndGet(query_store);


    //lancio la query di inserimento del prodotto
    string query_insert = "INSERT INTO favourites (id_store, id_cust, id_prov) VALUES ('"+to_string(id_store)+"',  '"+to_string(id_client)+"', '"+to_string(id_prov)+"');";
    db->exec(query_insert);

}
void dbFavouritesManager::remove_all() {

    //metodo per rimuovere tutti i prodotti dai favoriti
    // una volta effettuato l'ordine da quest'ultimo

    //prendo l'id dell'utente che sta usando il programma
    int id = user->get_db_id();

    //lancio la query di delete dal db
    string query = "DELETE FROM cart WHERE id_user = '"+ to_string(id)+"'";
    db->exec(query);
}

void dbFavouritesManager::remove_prod(int id_store) {

    //metodo che rimuove un prodotto dalla lista
    string query = "DELETE FROM favourites WHERE id_store = '"+ to_string(id_store)+"'";
    db->exec(query);


    fav->remove_one(id_store);
}

void dbFavouritesManager::select() {

    //metodo che prende i valori di tutti i prodotti
    // presenti nella lista dei favourites

    //prendo l'id dell'utente che sta usando il programma
    int id = user->get_db_id();
    string us_client= user->get_username();
    fav=make_shared<Favourites>(us_client);

    //lancio la query di selezione
    string select = "SELECT desc_prod, price_product, username,  available_quantity, id_sub, store.id FROM users, favourites, store WHERE favourites.id_prov = users.id AND id_store = store.id AND id_cust ='"+to_string(id) +"' ORDER BY username;";
    SQLite::Statement query(*db,select);

    //inserisco i valori nella matrice e la restituisco
    while (query.executeStep()){

        string desc = query.getColumn(0).getText();
        double price = query.getColumn(1).getDouble();
        string username_prov = query.getColumn(2).getText();
        int available_q= query.getColumn(3);
        int id_sub= query.getColumn(4);
        int id_store=query.getColumn(5);

        string select_sub_name= "SELECT name FROM subcategories WHERE id = '"+to_string(id_sub) +"'";
        string sub_name=db->execAndGet(select_sub_name);

        prod->set_desc(desc);
        prod->set_price(price);
        prod->set_username_prov(username_prov);
        prod->set_id_store(id_store);
        prod->set_available_quantity(available_q);
        prod->set_subcategory(sub_name);
        prod->set_quantity(0);

        fav->add_product(prod);
    }

}
