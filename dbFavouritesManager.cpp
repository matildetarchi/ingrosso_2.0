//
// Created by Andrea Lipperi on 15/06/23.
//

#include "dbFavouritesManager.h"

void dbFavouritesManager::add_to_db() {

    //metodo che aggiunge un prodotto alla lista dei favourites
    //prendo da db i valori di id dell'utente che sta usando il programma
    // e del fornitore del prodotto da inserire
    string query_cust="SELECT id FROM users WHERE username='"+username_cust+"'";
    int id_cust=db.execAndGet(query_cust).getInt();

    string query_prov="SELECT id FROM users WHERE username='"+username_prov+"'";
    int id_prov=db.execAndGet(query_prov).getInt();

    //lancio la query che inserisco il prodotto
    string query_insert="INSERT INTO favourites (id_store,id_cust, id_prov) VALUES ("+to_string(id_product)+", "+to_string(id_cust)+","+to_string(id_prov)+");";
    db.exec(query_insert);

}

void dbFavouritesManager::remove_prod(int id) {

    //metodo che rimuove un prodotto dalla lista
    string query="DELETE FROM favourites WHERE id = "+ to_string(id)+"";
    db.exec(query);

}

vector<vector<string>> dbFavouritesManager::select(const string &username) {

    //metodo che prende i valori di tutti i prodotti
    // presenti nella lista dei favourites

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query_user).getInt();

    //creo una matrice di stringhe cche conterrà i valori
    vector<vector<string>> mat;

    //lancio la query di selezione
    string select="SELECT desc_prod, price_product, username, store.id, favourites.id FROM users,favourites,store WHERE favourites.id_prov=users.id AND id_store=store.id AND id_cust="+to_string(id) +" ORDER BY username;";
    SQLite::Statement query(db,select);

    //inserisco i valori nella matrice e la restituisco
    int m=0;
    int n=0;
    vector<string> vector;
    string data;
    while (query.executeStep()){
        while (n<5) {
            data=query.getColumn(n).getText();
            vector.push_back(data);
            n++;
        }
        mat.push_back(vector);
        vector.clear();
        n=0;
        m++;
    }
    return mat;

}

int dbFavouritesManager::select_count(const string &username) {

    //metodo che restituisce il numero di prodotti nella lista

    //prendo il valore dell'id dell'utente che usa il programma
    string query = "SELECT id FROM users WHERE username ='" + username + "'";
    int id = db.execAndGet(query).getInt();

    //lancio la query select count(*) e restituisco il valore
    string query_select_count = "SELECT count(*) FROM favourites WHERE id_cust =" + to_string(id) + "";
    int count = db.execAndGet(query_select_count).getInt();

    return count;

}
