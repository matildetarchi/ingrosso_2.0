//
// Created by Andrea Lipperi on 15/06/23.
//

#include "dbFavouritesManager.h"



dbFavouritesManager::dbFavouritesManager(const shared_ptr<Database>& d) {
    db = d->get_db();
    prod = make_shared<Product>();

}

void dbFavouritesManager::add_to_db() {

    //metodo che aggiunge un prodotto alla lista dei favourites
    fav= client->get_fav();
    int index = fav->get_num_prod()-1;

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
    int id = client->get_db_id();

    //lancio la query di delete dal db
    string query = "DELETE FROM cart WHERE id_user = '"+ to_string(id)+"'";
    db->exec(query);

    fav->remove_all();
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
    int id = client->get_db_id();

    string us_client= client->get_username();
    fav=make_shared<Favourites>(us_client);
    string query_count = "SELECT count(*) FROM users, favourites, store WHERE favourites.id_prov = users.id AND id_store = store.id AND id_cust ='"+to_string(id) +"'";
    int count = db->execAndGet(query_count).getInt();
    if (count >0) {
        //lancio la query di selezione
        string select =
                "SELECT desc_prod, price_product, username,  available_quantity, id_sub, store.id FROM users, favourites, store WHERE favourites.id_prov = users.id AND id_store = store.id AND id_cust ='" +
                to_string(id) + "' ORDER BY username;";
        SQLite::Statement query(*db, select);

        //inserisco i valori nella matrice e la restituisco
        while (query.executeStep()) {
            string desc = query.getColumn(0).getText();
            double price = query.getColumn(1).getDouble();
            string username_prov = query.getColumn(2).getText();
            int available_q = query.getColumn(3);
            int id_sub = query.getColumn(4);
            int id_store = query.getColumn(5);

            string select_sub_name = "SELECT name FROM subcategories WHERE id = '" + to_string(id_sub) + "'";
            string sub_name = db->execAndGet(select_sub_name);


            shared_ptr<Product> product = make_shared<Product>(desc,price,0,available_q,username_prov,sub_name);
            product->set_id_store(id_store);
            fav->add_product(product);
        }
        client->set_fav(fav);
    }
}

int dbFavouritesManager::select_count_of_prod(){

    //seleziono l'id del cliente che sta usando il programma
    int id_client = client->get_db_id();
    //prendo la quantità di prodotti presenti
    string query_select_count = "SELECT count(*) FROM favourites WHERE id_cust ='" + to_string(id_client) + "'";
    int count = db->execAndGet(query_select_count).getInt();
    return count;
}

bool dbFavouritesManager::control_if_exist(const shared_ptr<Product>& p) {

    string select_id_prov = "SELECT id FROM users WHERE username = '"+p->get_username_prov()+"'";
    cout << select_id_prov << endl;
    int id_prov = db->execAndGet(select_id_prov).getInt();
    string select_prod = "SELECT count(*) FROM store, favourites WHERE id_store = store.id AND id_cust = "+ to_string(client->get_db_id()) +" AND desc_prod = '" + p->get_desc() + "' AND favourites.id_prov="+
                         to_string(id_prov)+"";
    cout << select_prod << endl;
    int count = db->execAndGet(select_prod);
    if(count > 0)
        return true;
    else
        return false;
}
