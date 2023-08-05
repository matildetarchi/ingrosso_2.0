//
// Created by Matilde Tarchi on 16/06/23.
//

#include "dbUserManager.h"


dbUserManager::dbUserManager(SQLite::Database *d) {
    db=d;
}

bool dbUserManager::access_reg(const string &email, const string &psw, int control) {
    //funzione per l'accesso o la registrazione al programma
    //control = 0 accesso normale
    //control = 1 per controllo se utente già esistente in caso di registrazione

    int num_found =0;
    //lancio la query di selezione di tutti gli utenti dal db
    //controllo cosa deve fare il programma
    SQLite::Statement query(*db, "SELECT * FROM users");
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
void dbUserManager::add_to_db() {

    //funzione che aggiunge un nuovo utente al database

    //lancio la query di insert
    string query="INSERT INTO users (type, business_name, address, id_city, email, password, username) VALUES ('" + user->get_type() + "', '" +user->get_bus_name() + "', '" + user->get_address() + "', " + user->get_city() + ", '" + user->get_email() + "', '" + user->get_psw() + "', '" + user->get_username() + "');";
    db->exec(query);

}
bool dbUserManager::remove_from_db(const string &username, const string &type) {
    //funzione per rimuovere l'utente

    //seleziono l'id dell'utente che vuole essere cancellato
    int id = user->get_db_id();

    //controllo il tipo di utente
    //'F' fornitore, 'C' cliente
    if (type=="F") {
        //controllo che il fornitore non abbia ordini in sospeso
        //se li ha ritorno 0 e non gli permetto di cancellarsi
        string query_count_orders="SELECT count(*) FROM orders WHERE status='S' AND id_prov="+to_string(id)+"";
        int count_ord = db->execAndGet(query_count_orders).getInt();
        if (count_ord > 0) {
            return false;
        }

        //controllo che il fornitore non abbia prodotti
        //nella lista dei preferiti di qualcuno
        //se li ha ritorno 0
        //non gli permetto di cancellarsi
        string query_count_fav="SELECT count(*) FROM favourites WHERE id_prov="+to_string(id)+"";
        int count_fav = db->execAndGet(query_count_fav).getInt();
        if (count_fav > 0) {
            return false;
        }

        //controllo che il fornitore non abbia prodotti
        //nel carrello di qualcuno
        //se li ha ritorno 0
        //non gli permetto di cancellarsi
        string query_count_cart="SELECT count(*) FROM cart WHERE id_prov="+to_string(id)+"";
        int count_cart = db->execAndGet(query_count_cart).getInt();
        if (count_cart > 0) {
            return false;
        }

        //se il fornitore non è presente da nessuna parte
        //elimino i dati degli ordini di quell'utente
        string query_del_ord="DELETE FROM orders WHERE id_prov = "+to_string(id)+"";
        db->exec(query_del_ord);

        //se il fornitore non è presente da nessuna
        //parte elimino tutti i suoi prodotti dal magazzino
        string query_del_store="DELETE FROM store WHERE id_prov = "+to_string(id)+"";
        db->exec(query_del_store);

        //infine cancello l'utente stesso
        string query="DELETE FROM users WHERE id = "+ to_string(id)+"";
        db->exec(query);

        return true;

    } else if (type=="C") {

        //controllo che il cliente non abbia ordini in sospeso
        //se li ha restituisco 0
        //non gli permetto di cancellarsi
        string query_count_orders="SELECT count(*) FROM orders WHERE status='S' AND id_cust="+to_string(id)+"";
        int count_ord = db->execAndGet(query_count_orders).getInt();
        if (count_ord > 0) {
            return false;
        }

        //se non li ha

        //elimino i dati del carrello di quel cliente
        string query_del_cart="DELETE FROM cart WHERE id_user = "+to_string(id)+"";
        db->exec(query_del_cart);

        //elimino i dati della lista dei preferiti del cliente
        string query_del_fav="DELETE FROM favourites WHERE id_cust = "+to_string(id)+"";
        db->exec(query_del_fav);

        //elimino i dati degli ordini di quell'utente
        string query_del_ord="DELETE FROM orders WHERE id_client = "+to_string(id)+"";
        db->exec(query_del_ord);

        //infine elimino l'utente stesso
        string query_del_user="DELETE FROM users WHERE id = "+to_string(id)+"";
        db->exec(query_del_user);

        return true;

    }
    return true;
}
void dbUserManager::changeData(const string &username_old, const string &new_address, const string &new_city, const string &new_psw, const string &new_email, const string &new_username) {

    //funzione per cambiare i dati dell'utente

    //prendo i valore dell'id dell'utente che vuole modificare i suoi dati
    int id = user->get_db_id();

    string query_city_id ="SELECT id FROM cities WHERE name='"+new_city+"'";
    int id_city=db->execAndGet(query_city_id).getInt();

    //lancio la query di update dei dati
    string query="UPDATE users SET address='"+new_address+"', id_city="+to_string(id_city)+", email='"+new_email+"', password = '"+new_psw+"', username='"+new_username+"' WHERE id = "+ to_string(id)+"";
    db->exec(query);

    user->set_address(new_address);
    user->set_city(new_city);
    user->set_email(new_email);
    user->set_password(new_psw);
    user->set_username(new_username);

}

void dbUserManager::select_data(const string &username) {

    //funzione per selezionare dal database tutti i dati dell'utente

    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    string select="SELECT id, address, id_city, email, password, business_name FROM users WHERE username='"+username+"';";
    SQLite::Statement query(*db,select);
    int id_city=query.getColumn(1).getInt();
    string select_city_name="SELECT name FROM city WHERE id="+to_string(id_city)+"";
    string city_name=db->execAndGet(select_city_name).getString();
    string select_type="SELECT type FROM users WHERE username="+username+"";
    string type=db->execAndGet(select_type).getString();


    int dbId = query.getColumn(0).getInt();
    string address=query.getColumn(1).getText();
    string email=query.getColumn(2).getText();
    string psw=query.getColumn(3).getText();
    string bus_name=query.getColumn(4).getText();
    user->set_id_db(dbId);
    user->set_city(select_city_name);
    user->set_password(psw);
    user->set_email(email);
    user->set_address(address);
    user->set_bus_name(bus_name);


}
const string dbUserManager::select_type(const std::string &email) {

    //metodo per selezionare il tipo di un utente

    //lancio la query e restituisco il valore
    string query="SELECT type FROM users WHERE email='"+email+"'";
    string type=db->execAndGet(query).getString();
    return type;

}
const string dbUserManager::select_username(const std::string &email) {

    //metodo per selezionare l'username di un utente

    //lancio la query e restituisco il valore
    string query="SELECT username FROM users WHERE email='"+email+"'";
    string username=db->execAndGet(query).getString();
    return username;

}

void dbUserManager::changePsw(const std::string &email, const std::string &new_psw) {

    //metodo per permettera all'utente di cambiare la prorpria password

    //lancio la query di update
    string query="UPDATE users SET password='"+new_psw+"' WHERE email='"+email+"'";
    db->exec(query);

}

