//
// Created by Andrea Lipperi on 16/11/22.
//

#define only_pending 0
#include "orderProduct.h"
#include "database.h"
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <string>
using namespace std;

OrderProduct::OrderProduct() {

}

OrderProduct::OrderProduct(int quant, int cod_product, const string &st, const string &d, const string &client, const string &provider, int id_ord){

    quantity=quant;
    id_product=cod_product;
    username_cust=client;
    status=st;
    date_order=d;
    username_prov=provider;
    id_order=id_ord;

}


void OrderProduct::add() {

    //metodo che aggiunge un ordine al database

    //seleziono i valori id dell'utente che usa il programma
    // e del fornitore a cui sarà inviato l'ordine
    string query_prov="SELECT id FROM users WHERE username='"+username_prov+"'";
    int id_prov=db.execAndGet(query_prov);

    string query_cust="SELECT id FROM users WHERE username='"+username_cust+"'";
    int id_cust=db.execAndGet(query_cust);


    //lancio la query che inserisce l'ordine
    string query_insert="INSERT INTO orders (quantity,status, date_order, id_store,id_cust, id_prov, id_single_order) VALUES (" + to_string(quantity) + ",'S','"+date_order+"', " + to_string(id_product) + ","+
                        to_string(id_cust)+","+
                        to_string(id_prov)+","+ to_string(id_order)+");";

    db.exec(query_insert);

}

void OrderProduct::changeStatus(const string &username,const string &cod_order, const string &new_status) {

    //metodo che cambia lo status dell'ordine da sospeso(S) a approvato(A) o rifiutato(D)

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query_user).getInt();
    int order=stoi(cod_order);

    //lancio la query di modifica
    string query = "UPDATE orders SET status = '"+new_status+"' WHERE id_single_order = " + to_string(order) + " AND id_prov = " +to_string(id) + ";";
    db.exec(query);

}

int OrderProduct::select_count_for_provider(const std::string &username, int control) {

    //metodo che prende quanti ordini ci sono in db,
    // con la scelta di poter vedere o solo quelli in sopseso(only_pending)
    //o tutti

    //prendo il valore dell'id dell'utente che sta usando il programma
    string query="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query).getInt();
    string query_select_count;

    //controllo di quali ordini si vuole sapere la quantità,
    // lancio la query
    //e restituisco il valore
    if (control==only_pending) {
        query_select_count =
                "SELECT count(DISTINCT id_single_order) FROM orders WHERE id_prov =" + to_string(id) +
                " AND status='S'";
    } else {
        query_select_count =
                "SELECT count(DISTINCT id_single_order) FROM orders WHERE id_prov =" + to_string(id) +
                "";
    }
    int count = db.execAndGet(query_select_count).getInt();
    return count;

}
int OrderProduct::select_count_for_client(const string &username, int control) {

    //metodo usato per la parte relaitva ai clienti
    // per sapere quanti ordini ci sono nel databse

    //prendo il vallore dell'id dell'utente che usa il programma
    string query="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query).getInt();

    //controllo di quali ordini si vuole sapere la quantità,
    // lancio la query
    //e restituisco il valore
    string query_select_count;
    if (control==only_pending) {
        query_select_count = "SELECT count(DISTINCT id_single_order) FROM orders WHERE id_cust =" + to_string(id) +
                             " AND status='S'";
    } else {

        query_select_count = "SELECT count(DISTINCT id_single_order) FROM orders WHERE id_cust =" + to_string(id) +
                             "";
    }
    int count = db.execAndGet(query_select_count).getInt();
    return count;

}

vector<vector<string>> OrderProduct::select_for_provider(const std::string &username, int control, const std::string &order) {

    //metodo che restituisce una matrice di stringhe
    // contenente i dati generali degli ordini di un fornitore

    //prendo il valore dell'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+username+"'";
    int id = db.execAndGet(query_user).getInt();

    //creo una matrice di stringhe che conterrà i valori
    vector<vector<string>> mat;
    string select;

    //controllo il tipo di ordinamento richiesto
    string str_order;
    if (order == "Code Order") {
        str_order ="id_single_order";
    } else if (order == "Customer Name") {
        str_order ="username";
    } else if (order == "Date Order") {
        str_order ="date_order";
    } else {
        str_order =order;
    }

    //controllo di quali tipo di ordini si vuole sapere i dati
    //only_pending=0 solo in sospeso
    //poi quindi creo le colonne della matrice
    //lancio la query e popolo la matrice per poi lanciarla
    vector<string> vector;
    string data;
    if (control==only_pending) {
        select ="SELECT DISTINCT id_single_order, username, date_order FROM users, orders WHERE id_cust=users.id AND status='S' AND id_prov=" +
                to_string(id) + " ORDER BY "+str_order+"";

        SQLite::Statement query(db, select);
        int m = 0;
        int n = 0;
        while (query.executeStep()) {
            while (n < 3) {
                data = query.getColumn(n).getText();
                vector.push_back(data);
                n++;
            }
            mat.push_back(vector);
            vector.clear();
            n = 0;
            m++;
        }
    } else {

        select ="SELECT DISTINCT id_single_order, username, date_order, CASE WHEN (status='S') THEN 'Pending' WHEN (status='D') THEN 'Denied' ELSE 'Accepted' END FROM users, orders WHERE id_cust=users.id AND id_prov="+to_string(id)+" ORDER BY "+str_order+"";
        SQLite::Statement query(db, select);
        int m = 0;
        int n = 0;
        while (query.executeStep()) {
            while (n < 4) {
                data = query.getColumn(n).getText();
                vector.push_back(data);
                n++;
            }
            mat.push_back(vector);
            vector.clear();
            n = 0;
            m++;
        }
    }
    return mat;

}


vector<vector<string>> OrderProduct::select_single_order_for_provider(const std::string &username,const std::string &cod_order) {

    //metodo che prende i dati di un singolo ordine selezionato in precedenza

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+username+"'";
    int id = db.execAndGet(query_user).getInt();

    //creo la matrice di stringhe che conterrà i valori
    vector<vector<string>> mat;


    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    int order=stoi(cod_order);
    vector<string> vector;
    string data;
    string select="SELECT quantity,price_product*quantity,desc_prod,available_quantity  FROM store, orders WHERE id_store=store.id AND orders.id_prov="+to_string(id)+" AND id_single_order="+to_string(order)+"";
    SQLite::Statement query(db,select);
    int m=0;
    int n=0;
    while (query.executeStep()){
        while (n<4) {
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

int OrderProduct::select_count_single_order_for_provider(const std::string &username, const std::string &cod_order) {

    //metodo per sapere quanti prodotti sono presenti
    // all'interno di un singolo ordine

    //prendo lò'id dell'utente che usa il programma
    string query="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query).getInt();

    //lancio la query e restituisco il valore
    int order=stoi(cod_order);
    string query_select_count="SELECT count(*) FROM orders WHERE id_prov ="+ to_string(id)+" AND id_single_order="+to_string(order)+"";
    int count = db.execAndGet(query_select_count).getInt();
    return count;

}

vector<vector<string>> OrderProduct::select_for_client(const string &username, int control, const string &order) {

    //matodo che prende i dati generali degli ordini di un cliente

    //prendo il valore dell'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+username+"'";
    int id = db.execAndGet(query_user).getInt();

    //creo la matrice di stringhe che conterrà i valori
    vector<vector<string>> mat;

    //controllo il tipo di ordinamento richiesto
    string str_order;
    if (order == "Code Order") {
        str_order ="id_single_order";
    } else if (order == "Provider Name") {
        str_order ="username";
    } else if (order == "Date Order") {
        str_order ="date_order";
    } else {
        str_order =order;
    }

    //controllo la tipologia di ordini dei quali si vuole sapere i dati
    //only_pending=0 solo in sospeso
    //setto il numero di colonne della matrice
    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    vector<string> vector;
    string data;
    if (control==only_pending) {

        string select ="SELECT DISTINCT id_single_order, username, date_order FROM users, orders WHERE id_prov=users.id AND status='S' AND id_cust=" +
                       to_string(id) + " ORDER BY "+str_order+"";
        SQLite::Statement query(db, select);
        int m = 0;
        int n = 0;
        while (query.executeStep()) {
            while (n < 3) {
                data = query.getColumn(n).getText();
                vector.push_back(data);
                n++;
            }
            mat.push_back(vector);
            vector.clear();
            n = 0;
            m++;
        }
    } else {
        string select ="SELECT DISTINCT id_single_order, username, date_order, CASE WHEN (status='S') THEN 'Pending' WHEN (status='D') THEN 'Denied' ELSE 'Accepted' END FROM users, orders WHERE id_prov=users.id AND id_cust="+to_string(id)+" ORDER BY "+str_order+"";
        SQLite::Statement query(db, select);
        int m = 0;
        int n = 0;
        while (query.executeStep()) {
            while (n < 4) {
                data = query.getColumn(n).getText();
                vector.push_back(data);
                n++;
            }
            mat.push_back(vector);
            vector.clear();
            n = 0;
            m++;
        }

    }
    return mat;

}

int OrderProduct::select_count_single_order_for_client(const string &username, const string &cod_order, const string &us_prov) {

    //metodo che prende il numero di prodotti
    //all'interno di un singolo ordine per i clienti

    //prendo l'id dell'utente che sta usando il programma
    string query="SELECT id FROM users WHERE username ='"+ username+"'";
    int id = db.execAndGet(query).getInt();

    //prendo l'id del fornitore al quale appartine il prodotto
    string query_prov="SELECT id FROM users WHERE username ='"+ us_prov+"'";
    int id_prov = db.execAndGet(query_prov).getInt();

    //lancio la query e restituisco il valore
    int order=stoi(cod_order);
    string query_select_count="SELECT count(*) FROM orders WHERE id_cust ="+ to_string(id)+" AND id_single_order="+to_string(order)+" AND id_prov="+ to_string(id_prov)+"";
    int count = db.execAndGet(query_select_count).getInt();
    return count;

}

vector<vector<string>> OrderProduct::select_single_order_for_client(const std::string &username, const std::string &cod_order, const string &us_prov)  {

    //metodo che prende i dati di un singolo ordine selezionato in precedenza

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+username+"'";
    int id = db.execAndGet(query_user).getInt();

    //prendo l'id del fornitore al quale è inviato l'ordine
    string query_prov="SELECT id FROM users WHERE username ='"+us_prov+"'";
    int id_prov = db.execAndGet(query_prov).getInt();

    //creo la matrice che conterrà i dati
    vector<vector<string>> mat_client;

    //lancio la query
    //popolo la matrice
    //restituisco i dati
    int order=stoi(cod_order);
    string select="SELECT quantity,price_product*quantity,desc_prod  FROM store, orders WHERE id_store=store.id AND orders.id_cust="+to_string(id)+" AND id_single_order="+
                  to_string(order)+" AND orders.id_prov="+ to_string(id_prov)+"";

    SQLite::Statement query(db,select);

    vector<string> vector;
    string data;
    int m=0;
    int n=0;
    while (query.executeStep()){
        while (n<3) {
            data = query.getColumn(n).getText();
            vector.push_back(data);
            n++;
        }
        mat_client.push_back(vector);
        vector.clear();
        n=0;
        m++;
    }
    return mat_client;

}
void OrderProduct::cancel_order(const std::string &username, const std::string &cod_order, const string &us_prov) {

    //metodo che permette a un utente di annullare il proprio ordine

    //prendo l'id dell'utente che sta usando il programma
    string query_user="SELECT id FROM users WHERE username ='"+username+"'";
    int id = db.execAndGet(query_user).getInt();

    //prendo l'id del fornitore al quale è stato inviato l'ordine
    string query_prov="SELECT id FROM users WHERE username ='"+us_prov+"'";
    int id_prov = db.execAndGet(query_prov).getInt();

    //lancio la query delete
    int order=stoi(cod_order);
    string cancel="DELETE FROM orders WHERE id_single_order="+ to_string(order)+ " AND id_cust="+ to_string(id) +" AND id_prov="+to_string(id_prov)+"";
    db.exec(cancel);

}

int OrderProduct::select_id_last_order(const string &username_prov) {
    //metodo per ottenere il codice dell'ultimo ordine fatto a un fornitore

    //prendo l'id del fornitore
    string query_user="SELECT id FROM users WHERE username ='"+username_prov+"'";
    int id_prov = db.execAndGet(query_user).getInt();

    //lancio la select del MAX(id) e ritorno il risultato
    string query_id="SELECT MAX(id_single_order) FROM orders WHERE id_prov="+ to_string(id_prov)+"";
    int id_single_order=db.execAndGet(query_id).getInt();

    return id_single_order;

}


