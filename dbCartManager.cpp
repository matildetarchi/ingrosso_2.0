//
// Created by Andrea Lipperi on 15/06/23.
//

#include "dbCartManager.h"

void dbCartManager::add_to_db(Cart *cart) {

    //metodo per aggiungere al carrello un nuovo prodotto
    int index=cart->get_num_prod()-1;
    //prendo l'id dell'utente che sta usando il programma e
    // del fornitore del prodotto che sto mettendo nel carrello
    string query_user="SELECT id FROM users WHERE username='"+cart->get_user(index)+"'";
    int id_user=db.execAndGet(query_user);

    string query_prov="SELECT id FROM users WHERE username='"+cart->get_prov(index)+"'";
    int id_prov=db.execAndGet(query_prov);

    //inserisco i dati nel db
    string query_insert="INSERT INTO cart (quantity, id_store,id_user, id_prov) VALUES (" + to_string(cart->get_quantity(index)) + ", " + to_string(cart->get_id_prod(index)) + ","+ to_string(id_user)+","+to_string(id_prov)+")";

    db.exec(query_insert);

}

void dbCartManager::remove_all(const string &username) {

    //metodo per rimuovere tutti i prodotti dal carello
    // una volta effettuato l'ordine da quest'ultimo

    //prendo l'id dell'utente che sta usando il programma
    string query_select="SELECT id FROM users WHERE username ='"+username+"'";
    int id = db.execAndGet(query_select).getInt();

    //lancio la query di delete dal db
    string query="DELETE FROM cart WHERE id_user = "+ to_string(id)+"";
    db.exec(query);

    Cart cart;
    cart.remove_all(username);

}

void dbCartManager::remove_prod(int id) {

    //metodo per eliminare un solo prodotto dal carrello

    string query="DELETE FROM cart WHERE id = "+ to_string(id)+"";
    db.exec(query);

    Cart cart;
    cart.remove_one(id);

}

int dbCartManager::select_count(const string &username) {

    //metodo per sapere quanti prodotti ha l'utente nel carrello

    //prendo l'id dell'utente che sta usando il programma
    string query="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query).getInt();

    //lancio la query select count(*) e restituisco il valore
    string query_select_count="SELECT count(*) FROM cart WHERE id_user ="+ to_string(id)+"";
    int count = db.execAndGet(query_select_count).getInt();
    return count;



}

void dbCartManager::select(const string &username) {

    //metodo per prendere i valori dei prodotti nel carrello dell'utente

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query_user).getInt();

    //lancio la query che prende i valori dal db
    string select="SELECT desc_prod, price_product, username, quantity FROM users,cart,store WHERE id_store=store.id AND store.id_prov=users.id AND id_user="+to_string(id) +" ORDER BY username;";
    SQLite::Statement query(db,select);

    //inserisco i valori all'interno della matrice e la restituisco
    while (query.executeStep()){

        string desc=query.getColumn(0).getText();
        double price=query.getColumn(1).getDouble();
        string username_prov=query.getColumn(2).getText();
        int quantity=query.getColumn(3).getInt();
        Cart *cart=new Cart(quantity,desc,price,username,username_prov);

    }

}



