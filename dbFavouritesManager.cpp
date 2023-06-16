//
// Created by Andrea Lipperi on 15/06/23.
//

#include "dbFavouritesManager.h"

void dbFavouritesManager::add_to_db(Favourites *new_fav) {

    //metodo che aggiunge un prodotto alla lista dei favourites
    int index = fav->get_num_prod()-1;

    //prendo da db i valori di id dell'utente che sta usando il programma
    // e del fornitore del prodotto da inserire
    string query_cust="SELECT id FROM users WHERE username='"+fav->get_cust()+"'";
    int id_cust=db.execAndGet(query_cust).getInt();

    string query_prov="SELECT id FROM users WHERE username='"+fav->get_prov(index)+"'";
    int id_prov=db.execAndGet(query_prov).getInt();

    string query_store="SELECT id FROM store WHERE desc_prod='"+fav->get_prod(index)+"' AND id_prov="+ to_string(id_prov)+"";
    int id_store=db.execAndGet(query_store);


    //lancio la query che inserisco il prodotto
    string query_insert="INSERT INTO favourites (id_store,id_cust, id_prov) VALUES ("+to_string(id_store)+", "+to_string(id_cust)+","+to_string(id_prov)+");";
    db.exec(query_insert);

}

void dbFavouritesManager::remove_prod(int id) {

    //metodo che rimuove un prodotto dalla lista
    string query="DELETE FROM favourites WHERE id = "+ to_string(id)+"";
    db.exec(query);

    fav->remove_one(id);

}

void dbFavouritesManager::select(const string &username) {

    //metodo che prende i valori di tutti i prodotti
    // presenti nella lista dei favourites

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query_user).getInt();

    //lancio la query di selezione
    string select="SELECT desc_prod, price_product, username FROM users,favourites,store WHERE favourites.id_prov=users.id AND id_store=store.id AND id_cust="+to_string(id) +" ORDER BY username;";
    SQLite::Statement query(db,select);

    //inserisco i valori nella matrice e la restituisco

    while (query.executeStep()){

        string desc=query.getColumn(0).getText();
        double price=query.getColumn(1).getDouble();
        string username_prov=query.getColumn(2).getText();
        Favourites *fav_sel= new Favourites(desc,price,username,username_prov);

    }

}
