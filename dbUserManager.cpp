//
// Created by Matilde Tarchi on 16/06/23.
//

#include "dbUserManager.h"



dbUserManager::dbUserManager(const shared_ptr<Database>& d) {
    db = d->get_db();

}

bool dbUserManager::access_reg(const string &email, const string &psw, int control) {
    //funzione per l'accesso o la registrazione al programma
    //control = 0 accesso normale
    //control = 1 per controllo se utente già esistente in caso di registrazione

    int num_found = 0;
    //lancio la query di selezione di tutti gli utenti dal db
    //controllo cosa deve fare il programma
    SQLite::Statement query(*db, "SELECT * FROM users");
    query.reset();

    if (control == accesso) {
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
    } else if(control == registrazione){
        //controllo che la mail non sia già stata usata per un utente
        //se si restituisco false almtrimenti true
        while (query.executeStep()){
            if (query.getColumn(4).getText() == email) {
                return false;
            }
        }
    }
    return true;
}

void dbUserManager::add_to_db() {

    //funzione che aggiunge un nuovo utente al database

    //lancio la query di insert
    string query_id_city = "SELECT id FROM cities WHERE name = '"+user->get_city()+"'";
    int id_city = db->execAndGet(query_id_city);

    string query = "INSERT INTO users (type, business_name, address, id_city, email, password, username) VALUES ('" + user->get_type() + "', '" +user->get_bus_name() + "', '" + user->get_address() + "', '" +
            to_string(id_city) + "', '" + user->get_email() + "', '" + user->get_psw() + "', '" + user->get_username() + "')";
    db->exec(query);
    string i_u = "SELECT id FROM users WHERE email= '" + user->get_email() + "'";
    int id_user = db->execAndGet(i_u);
    user->set_id_db(id_user);
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
        string query_count_orders = "SELECT count(*) FROM orders, orders_details, store WHERE status = 'S' AND id_order = orders.id AND id_product = store.id AND id_prov = '"+to_string(id)+"'";
        int count_ord = db->execAndGet(query_count_orders).getInt();
        if (count_ord > 0) {
            return false;
        }

        //controllo che il fornitore non abbia prodotti
        //nella lista dei preferiti di qualcuno
        //se li ha ritorno 0
        //non gli permetto di cancellarsi
        string query_count_fav = "SELECT count(*) FROM favourites WHERE id_prov = '"+to_string(id)+"'";
        int count_fav = db->execAndGet(query_count_fav).getInt();
        if (count_fav > 0) {
            return false;
        }

        //controllo che il fornitore non abbia prodotti
        //nel carrello di qualcuno
        //se li ha ritorno 0
        //non gli permetto di cancellarsi
        string query_count_cart = "SELECT count(*) FROM cart WHERE id_prov = '"+to_string(id)+"'";
        int count_cart = db->execAndGet(query_count_cart).getInt();
        if (count_cart > 0) {
            return false;
        }

        //se il fornitore non è presente da nessuna parte
        //elimino i dati degli ordini di quell'utente

        string sel_store = "SELECT id FROM store WHERE id_prov = '"+to_string(id)+"'";
        SQLite::Statement query_id_store(*db,sel_store);

        while(query_id_store.executeStep()) {

            int id_store = query_id_store.getColumn(0);
            string query_del_ord_details =
                    "DELETE FROM orders_details WHERE id_product = '" + to_string(id_store) + "'";
            db->exec(query_del_ord_details);

            string query_del_ord = "DELETE FROM orders WHERE id_product = '" + to_string(id_store) + "'";
            db->exec(query_del_ord_details);
        }


        //se il fornitore non è presente da nessuna
        //parte elimino tutti i suoi prodotti dal magazzino
        string query_del_store = "DELETE FROM store WHERE id_prov = '"+to_string(id)+"'";
        db->exec(query_del_store);

        //infine cancello l'utente stesso
        string query = "DELETE FROM users WHERE id = '"+ to_string(id)+"'";
        db->exec(query);


        return true;

    } else if (type=="C") {

        //controllo che il cliente non abbia ordini in sospeso
        //se li ha restituisco 0
        //non gli permetto di cancellarsi
        string query_count_orders = "SELECT count(*) FROM orders WHERE status='S' AND id_client = '"+to_string(id)+"'";
        int count_ord = db->execAndGet(query_count_orders).getInt();
        if (count_ord > 0) {
            return false;
        }

        //se non li ha
        //elimino i dati del carrello di quel cliente
        string query_count_cart = "SELECT count(*) FROM cart WHERE id_user = '"+to_string(id)+"' ";
        int num_prod_cart = db->execAndGet(query_count_cart);
        if(num_prod_cart > 0) {
            string query_del_cart = "DELETE FROM cart WHERE id_user = '" + to_string(id) + "'";
            db->exec(query_del_cart);
        }

        //elimino i dati della lista dei preferiti del cliente
        string query_count_fav = "SELECT count(*) FROM favourites WHERE id_cust = '"+to_string(id)+"' ";
        int num_prod_fav = db->execAndGet(query_count_fav);

        if(num_prod_fav > 0) {
            string query_del_fav = "DELETE FROM favourites WHERE id_cust = '" + to_string(id) + "'";
            db->exec(query_del_fav);
        }

        //elimino i dati degli ordini di quell'utente
        string query_count_ord = "SELECT count(*) FROM orders WHERE id_client = '"+to_string(id)+"' ";
        int num_prod_ord = db->execAndGet(query_count_ord);
        if(num_prod_ord > 0) {
            string query_id_order = "SELECT id FROM orders WHERE id_client = " + to_string(id) + "";
            SQLite::Statement query(*db, query_id_order);
            while (query.executeStep()) {
                int id_order = query.getColumn(0);
                string query_del_ord_details = "DELETE FROM orders_details WHERE id = " + to_string(id_order) + " ";
                db->exec(query_del_ord_details);
            }
            string query_del_ord = "DELETE FROM orders WHERE id_client = '" + to_string(id) + "'";
            db->exec(query_del_ord);
        }

        //infine elimino l'utente stesso
        string query_del_user = "DELETE FROM users WHERE id = '"+to_string(id)+"'";
        db->exec(query_del_user);

        return true;

    }
    user->delete_objects_of_user();
    return true;
}
void dbUserManager::change_data(const string &new_address, const string &new_city, const string &new_psw, const string &new_email, const string &new_username) {

    //funzione per cambiare i dati dell'utente

    //prendo i valore dell'id dell'utente che vuole modificare i suoi dati
    int id = user->get_db_id();
    int id_city = stoi(new_city);
    //lancio la query di update dei dati
    string query = "UPDATE users SET address='"+new_address+"', id_city = "+to_string(id_city)+", email = '"+new_email+"', password = '"+new_psw+"', username = '"+new_username+"' WHERE id = "+ to_string(id)+"";
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
    string select = "SELECT id, address, id_city, email, password, business_name FROM users WHERE username='"+username+"'";
    SQLite::Statement query(*db,select);
    if(query.executeStep()) {
        int id_city = query.getColumn(2);
        string select_city_name = "SELECT name FROM cities WHERE id = '" + to_string(id_city) + "'";
        string city_name = db->execAndGet(select_city_name).getString();
        string select_type = "SELECT type FROM users WHERE username = '" + username + "'";
        string type = db->execAndGet(select_type).getString();


        int dbId = query.getColumn(0).getInt();
        string address = query.getColumn(1).getText();
        string email = query.getColumn(3).getText();
        string psw = query.getColumn(4).getText();
        string bus_name = query.getColumn(5).getText();
        user->set_id_db(dbId);
        user->set_city(city_name);
        user->set_password(psw);
        user->set_email(email);
        user->set_address(address);
        user->set_bus_name(bus_name);
        user->set_username(username);
        user->set_type(type);
    }
    else {
        std::cout << "Nessun risultato trovato." << std::endl;
    }

}
string dbUserManager::select_type(const string &email) {

    //metodo per selezionare il tipo di un utente

    //lancio la query e restituisco il valore
    string query = "SELECT type FROM users WHERE email ='"+email+"'";
    string type = db->execAndGet(query).getString();
    return type;

}
string dbUserManager::select_username(const string &email) {

    //metodo per selezionare l'username di un utente

    //lancio la query e restituisco il valore
    string query = "SELECT username FROM users WHERE email ='"+email+"'";
    string username = db->execAndGet(query).getString();
    return username;

}

void dbUserManager::change_psw(const string &email, const string &new_psw) {

    //metodo per permettera all'utente di cambiare la prorpria password
    //lancio la query di update
    string query = "UPDATE users SET password='"+new_psw+"' WHERE email='"+email+"'";
    db->exec(query);

}

vector<shared_ptr<User>> dbUserManager::select_users(const string &type, const string &city) {
    vector<shared_ptr<User>> user_list;
    shared_ptr<User> single_user;
    string type_us;
    if (type=="C") {
        type_us = "F";
    } else {
        type_us = "C";
    }
    if (city != "All") {
        string select_id_city = "SELECT id FROM cities WHERE name = '"+city+"' ";
        int id_city = db->execAndGet(select_id_city);

        string user_data = "SELECT business_name, address, email, password, username, id FROM users WHERE type = '"+ type_us+"' AND id_city = "+
                           to_string(id_city)+"";
        SQLite::Statement query_user(*db,user_data);
        while(query_user.executeStep()){
            string b_n = query_user.getColumn(0).getText();
            string address = query_user.getColumn(1).getText();
            string email = query_user.getColumn(2).getText();
            string psw = query_user.getColumn(3).getText();
            string username = query_user.getColumn(4);
            int id_us = query_user.getColumn(5);
            if (type_us=="C") {
                single_user = make_shared<Client>(type_us, b_n, address, email, psw, username, city);
                single_user->set_id_db(id_us);
            } else {
                single_user = make_shared<Provider>(type_us, b_n, address, email, psw, username, city);
                single_user->set_id_db(id_us);
            }
            user_list.push_back(single_user);
        }
    } else {
        string user_data = "SELECT business_name, address, email, password, username, cities.name, users.id FROM users, cities WHERE type = '"+ type_us+"' AND cities.id=id_city";
        SQLite::Statement query_user(*db,user_data);
        while(query_user.executeStep()){
            string b_n = query_user.getColumn(0).getText();
            string address = query_user.getColumn(1).getText();
            string email = query_user.getColumn(2).getText();
            string psw = query_user.getColumn(3).getText();
            string username = query_user.getColumn(4).getText();
            string user_city = query_user.getColumn(5).getText();
            int id_us = query_user.getColumn(6).getInt();
            if (type_us=="C")
            {
                single_user = make_shared<Client>(type_us, b_n, address, email, psw, username, user_city);
                single_user->set_id_db(id_us);
            } else if (type_us=="F")
            {
                single_user = make_shared<Provider>(type_us, b_n, address, email, psw, username, user_city);
                single_user->set_id_db(id_us);
            }
            user_list.push_back(single_user);

        }
    }

    return user_list;
}


int dbUserManager::select_count_users(const string &type, const string &city) {
    int count;
    string type_us;
    if (type=="C"){
        type_us = "F";
    } else {
        type_us = "C";
    }
    if (city!="All") {
        string select_id_city= "SELECT id FROM cities WHERE name = '"+city+"' ";
        int id_city= db->execAndGet(select_id_city);

        string user_data = "SELECT count(*) FROM users WHERE type = '"+ type_us+"' AND id_city = "+
                           to_string(id_city)+"";
        count = db->execAndGet(user_data);
    } else {
        string user_data = "SELECT count(*) FROM users WHERE type = '"+ type_us+"'";
        count = db->execAndGet(user_data);
    }

    return count ;
}


void dbUserManager:: remove_user(const string &username){
    string query_del_user = "DELETE FROM users WHERE username = '"+username+"'";
    db->exec(query_del_user);
}
