//
// Created by dario on 15/06/2023.
//
#define only_pending 0
#include "dbOrdersManager.h"



void dbOrdersManager::add_to_db(Orders *orders) {

    //metodo che aggiunge un ordine al database
     int index= orders->get_num_prod()-1;
    //seleziono i valori id dell'utente che usa il programma
    // e del fornitore a cui sarà inviato l'ordine
    string query_prov="SELECT id FROM users WHERE username='"+orders->get_us_other(index)+"'";
    int id_prov=db.execAndGet(query_prov);

    string query_cust="SELECT id FROM users WHERE username='"+orders->get_username_user()+"'";
    int id_cust=db.execAndGet(query_cust);

    string query_id_store = "SELECT id FROM store WHERE desc_prod ='"+orders->get_desc_prod(index)+"' AND id_prov =" + to_string(id_prov) + ";";
    int id_store=db.execAndGet(query_id_store);
    //lancio la query che inserisce l'ordine
    string query_insert="INSERT INTO orders (quantity,status, date_order, id_store,id_cust, id_prov, id_single_order) VALUES (" + to_string(orders->get_quantity(index)) + ",'S','"+orders->get_date(index)+"', " + to_string(id_store) + ","+
                        to_string(id_cust)+","+
                        to_string(id_prov)+","+ to_string(index)+");";

    db.exec(query_insert);

}

void dbOrdersManager::changeStatus(const string &username, const string &cod_order, const string &new_status) {

    //metodo che cambia lo status dell'ordine da sospeso(S) a approvato(A) o rifiutato(D)

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query_user).getInt();
    int order=stoi(cod_order);

    //lancio la query di modifica
    string query = "UPDATE orders SET status = '"+new_status+"' WHERE id_single_order = " + to_string(order) + " AND id_prov = " +to_string(id) + ";";
    db.exec(query);


    tab_order.set_status(cod_order,new_status);

}


void dbOrdersManager::select_for_provider(const std::string &username, int control) {

    //metodo che restituisce una matrice di stringhe
    // contenente i dati generali degli ordini di un fornitore

    //prendo il valore dell'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+username+"'";
    int id = db.execAndGet(query_user).getInt();

    //controllo di quali tipo di ordini si vuole sapere i dati
    //only_pending=0 solo in sospeso
    //poi quindi creo le colonne della matrice
    //lancio la query e popolo la matrice per poi lanciarla
    string select ="SELECT id_single_order, username, date_order, status, desc_prod, price_product, quantity FROM users, orders, store WHERE id_cust=users.id AND id_store=store.id AND id_prov=" +
            to_string(id) + "";

    SQLite::Statement query(db, select);

    while (query.executeStep()) {
        int id_sing_order = query.getColumn(0).getInt();
        string username_cust = query.getColumn(1).getText();
        string date_order = query.getColumn(2).getText();
        string status = query.getColumn(3).getText();
        string desc_prod = query.getColumn(4).getText();
        double price = query.getColumn(5).getDouble();
        int quantity = query.getColumn(6).getInt();
        Orders *order =new Orders(quantity,desc_prod,price,status,date_order,username,username_cust,id_sing_order);
    }

}





void dbOrdersManager::select_for_client(const string &username, int control) {

    //matodo che prende i dati generali degli ordini di un cliente

    //prendo il valore dell'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+username+"'";
    int id = db.execAndGet(query_user).getInt();

    string select ="SELECT id_single_order, username, date_order, status, desc_prod, price_product, quantity FROM users, orders, store WHERE id_prov=users.id AND id_store=store.id AND id_cust=" +
                   to_string(id) + "";

    SQLite::Statement query(db, select);

    while (query.executeStep()) {
        int id_sing_order = query.getColumn(0).getInt();
        string username_prov = query.getColumn(1).getText();
        string date_order = query.getColumn(2).getText();
        string status = query.getColumn(3).getText();
        string desc_prod = query.getColumn(4).getText();
        double price = query.getColumn(5).getDouble();
        int quantity = query.getColumn(6).getInt();
        Orders *order =new Orders(quantity,desc_prod,price,status,date_order,username,username_prov,id_sing_order);
    }


}


void dbOrdersManager::cancel_order(const std::string &username, const std::string &cod_order, const string &us_prov) {

    //metodo che permette a un utente di annullare il proprio ordine

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+username+"'";
    int id = db.execAndGet(query_user).getInt();

    //prendo l'id del fornitore al quale è stato inviato l'ordine
    string query_prov="SELECT id FROM users WHERE username ='"+us_prov+"'";
    int id_prov = db.execAndGet(query_prov).getInt();

    //lancio la query delete
    int order=stoi(cod_order);
    string query_cancel="DELETE FROM orders WHERE id_single_order="+ to_string(order)+ " AND id_cust="+ to_string(id) +" AND id_prov="+to_string(id_prov)+"";
    db.exec(query_cancel);

    tab_order.remove_one(order);

}

int dbOrdersManager::select_id_last_order(const string &username_prov) {
    //metodo per ottenere il codice dell'ultimo ordine fatto a un fornitore

    //prendo l'id del fornitore
    string query_user="SELECT id FROM users WHERE username ='"+username_prov+"'";
    int id_prov = db.execAndGet(query_user).getInt();

    //lancio la select del MAX(id) e ritorno il risultato
    string query_id="SELECT MAX(id_single_order) FROM orders WHERE id_prov="+ to_string(id_prov)+"";
    int id_single_order=db.execAndGet(query_id).getInt();

    return id_single_order;

}


