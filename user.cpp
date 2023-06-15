//
// Created by Andrea Lipperi on 14/11/22.
//

#include "user.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "database.h"
#include <SQLiteCpp/Statement.h>
#include <string>
#define accesso 0
#define registrazione 1
using namespace std;

User::User() {}

User::User(const std::string &t, const std::string &bn,const std::string &a, const std::string &e, const std::string &psw, const std::string &us, int city){
    type = t;
    business_name= bn;
    address = a;
    id_city = city;
    email = e;
    pass = psw;
    username = us;
}

bool User::access_reg(const string &email, const string &psw, int control) {

    //funzione per l'accesso o la registrazione al programma

    //control = 0 accesso normale
    //control = 1 per controllo se utente già esistente in caso di registrazione

    int num_found =0;
    //lancio la query di selezione di tutti gli utenti dal db
    //controllo cosa deve fare il programma
    SQLite::Statement query(db, "SELECT * FROM users");
    query.reset();
    if (control==accesso) {
        //controllo se la mail e la password sono corretti
        //se si restituisco true altrimenti false
        while (query.executeStep()){
            if (query.getColumn(4).getText() == email && query.getColumn(5).getText() == psw) {
                num_found++;
            }
        }
        if (num_found == 0) {
            return false;
        } else {
            return true;
        }
    } else if(control==registrazione){
        //controllo che la mail non sia già stata usata per un utente
        //se si restituisco false almtrimenti true
        while (query.executeStep()){
            if (query.getColumn(4).getText() == email) {
                num_found++;
            }
        }
        if (num_found == 0) {
            return true;
        } else {
            return false;
        }
    }
    return true;
}
void User::add() {

    //funzione che aggiunge un nuovo utente al database

    //lancio la query di insert
    string query="INSERT INTO users (type, business_name, address, id_city, email, password, username) VALUES ('" + type + "', '" +business_name + "', '" + address + "', " + to_string(id_city) + ", '" + email + "', '" + pass + "', '" + username + "');";
    db.exec(query);

}
bool User::remove(const string &username, const string &type) {

    //funzione per rimuovere l'utente

    //seleziono l'id dell'utente che vuole essere cancellato
    string query_select_id="SELECT id FROM users WHERE username='"+username+"'";
    int id=db.execAndGet(query_select_id).getInt();

    //controllo il tipo di utente
    //'F' fornitore, 'C' cliente
    if (type=="F") {
        //controllo che il fornitore non abbia ordini in sospeso
        //se li ha ritorno 0
        //non gli permetto di cancellarsi
        string query_count_orders="SELECT count(*) FROM orders WHERE status='S' AND id_prov="+to_string(id)+"";
        int count_ord = db.execAndGet(query_count_orders).getInt();
        if (count_ord > 0) {
            return false;
        }

        //controllo che il fornitore non abbia prodotti
        //nella lista dei preferiti di qualcuno
        //se li ha ritorno 0
        //non gli permetto di cancellarsi
        string query_count_fav="SELECT count(*) FROM favourites WHERE id_prov="+to_string(id)+"";
        int count_fav = db.execAndGet(query_count_fav).getInt();
        if (count_fav > 0) {
            return false;
        }

        //controllo che il fornitore non abbia prodotti
        //nel carrello di qualcuno
        //se li ha ritorno 0
        //non gli permetto di cancellarsi
        string query_count_cart="SELECT count(*) FROM cart WHERE id_prov="+to_string(id)+"";
        int count_cart = db.execAndGet(query_count_cart).getInt();
        if (count_cart > 0) {
            return false;
        }

        //se il fornitore non è presente da nessuna
        //elimino i dati degli ordini di quell'utente
        string query_del_ord="DELETE FROM orders WHERE id_prov = "+to_string(id)+"";
        db.exec(query_del_ord);

        //se il fornitore non è presente da nessuna
        //parte elimino tutti i suoi prodotti dal magazzino
        string query_del_store="DELETE FROM store WHERE id_prov = "+to_string(id)+"";
        db.exec(query_del_store);

        //infine cancello l'utente stesso
        string query="DELETE FROM users WHERE id = "+ to_string(id)+"";
        db.exec(query);

        return true;

    } else if (type=="C") {

        //controllo che il cliente non abbia ordini in sospeso
        //se li ha restituisco 0
        //non gli permetto di cancellarsi
        string query_count_orders="SELECT count(*) FROM orders WHERE status='S' AND id_cust="+to_string(id)+"";
        int count_ord = db.execAndGet(query_count_orders).getInt();
        if (count_ord > 0) {
            return false;
        }

        //se non li ha

        //elimino i dati del carrello di quel cliente
        string query_del_cart="DELETE FROM cart WHERE id_user = "+to_string(id)+"";
        db.exec(query_del_cart);

        //elimino i dati della lista dei preferiti del cliente
        string query_del_fav="DELETE FROM favourites WHERE id_cust = "+to_string(id)+"";
        db.exec(query_del_fav);

        //elimino i dati degli ordini di quell'utente
        string query_del_ord="DELETE FROM orders WHERE id_cust = "+to_string(id)+"";
        db.exec(query_del_ord);

        //infine elimino l'utente stesso
        string query_del_user="DELETE FROM users WHERE id = "+to_string(id)+"";
        db.exec(query_del_user);

        return true;

    }
    return true;
}
void User::changeData(const string &username_old) {

    //funzione per cambiare i dati dell'utente

    //prendo i valore dell'id dell'utente che vuole modificare i suoi dati
    string query_id="Select id FROM users WHERE username='"+username_old+"'";
    int i=db.execAndGet(query_id).getInt();

    //lancio la query di update dei dati
    string query="UPDATE users SET address='"+address+"', id_city="+to_string(id_city)+", email='"+email+"', password = '"+pass+"', username='"+username+"' WHERE id = "+ to_string(i)+"";
    db.exec(query);

}

vector<string> User::select_data(const string &username) {

    //funzione per selezionare dal database tutti i dati dell'utente

    //creo il vettore di stringhe che conterrà i dati dell'utente
    std::vector<std::string> vector;

    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    string select="SELECT address, id_city, email, password, business_name FROM users WHERE username='"+username+"';";
    SQLite::Statement query(db,select);
    string data;
    int n=0;
    while (query.executeStep()){
        while (n<4) {
            data=query.getColumn(n).getText();
            vector.push_back(data);
            n++;
        }
        n=0;
    }
    return vector;

}
const string User::select_type(const std::string &email) {

    //metodo per selezionare il tipo di un utente

    //lancio la query e restituisco il valore
    string query="SELECT type FROM users WHERE email='"+email+"'";
    string type=db.execAndGet(query).getString();
    return type;

}
const string User::select_username(const std::string &email) {

    //metodo per selezionare l'username di un utente

    //lancio la query e restituisco il valore
    string query="SELECT username FROM users WHERE email='"+email+"'";
    string username=db.execAndGet(query).getString();
    return username;

}

void User::changePsw(const std::string &email, const std::string &new_psw) {

    //metodo per permettera all'utente di cambiare la prorpria password

    //lancio la query di update
    string query="UPDATE users SET password='"+new_psw+"' WHERE email='"+email+"'";
    db.exec(query);

}

vector<vector<string>> User::select_data_all_users(const string &type, const string &city, const string &control) {

    //metodo per prendere i dati di tutti i clienti se fatto da un fornitore
    //o di tutti i fornitore se fatto da un cliente

    //creo la matrice di stringhe che conterrà i dati degli utenti
    vector<vector<string>> mat;

    //controllo il tipo di ordinamento richiesto
    string order;
    if (control=="Business Name") {
        order = "business_name";
    } else if (control=="Username") {
        order = "username";
    } else if (control=="Email") {
        order = "email";
    } else if (control=="Address") {
        order = "address";
    } else if (control=="City") {
        order = "name";
    } else {
        order = control;
    }
    //controllo se si vuole sapere tutti gli utenti o di una particolare città
    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    string select;
    if (city=="All") {

        select = "SELECT business_name, username, email, address, name FROM users, cities WHERE cities.id=id_city AND type!='" + type + "' ORDER BY "+order+";";

    } else {
        //prendo il valore dell'id della città scelta
        string select_city="SELECT id FROM cities WHERE name='"+city+"'";
        int id=db.execAndGet(select_city).getInt();

        select = "SELECT business_name, username, email, address, name FROM users, cities WHERE cities.id=id_city AND type!='" + type + "' AND id_city="+to_string(id)+" ORDER BY "+order+";";

    }
    SQLite::Statement query(db, select);
    vector<string> vector;
    string data;
    int m = 0;
    int n = 0;
    while (query.executeStep()) {
        while (n < 5) {
            data = query.getColumn(n).getText();
            vector.push_back(data);
            n++;
        }
        mat.push_back(vector);
        vector.clear();
        n = 0;
        m++;
    }
    return mat;

}
int User::select_count_users(const string &type, const string &city) {
    //metodo che prende il numero di fornitori o clienti di una certa città

    //controllo se si vuole sapere il numero generale o di una particolare città
    string query;
    if (city=="All") {
        query="SELECT count(*) FROM users WHERE type!='"+type+"'";
    } else {
        //prendo il valore dell'id della città scelta
        string select_city="SELECT id FROM cities WHERE name='"+city+"'";
        int id=db.execAndGet(select_city).getInt();
        query="SELECT count(*) FROM users WHERE type!='"+type+"' AND id_city="+ to_string(id)+"";
    }
    int count = db.execAndGet(query).getInt();
    return count;
}
