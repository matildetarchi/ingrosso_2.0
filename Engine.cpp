//
// Created by dario on 16/06/2023.
//

#include "Engine.h"

Engine::Engine() {

        // Specifica il percorso del tuo database SQLite
        const std::string dbPath = "C:/Users/dario/CLionProjects/ingrosso_online/ingrossodb.sqlite";

        // Apri il database
        SQLite::Database database(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        std::cout << "Database aperto con successo." << std::endl;

        // Esegui le operazioni sul database qui



    db_cart = make_unique<dbCartManager>(&database);
    db_store = make_unique<dbStoreManager>(&database);
    db_order = make_unique<dbOrdersManager>(&database);
    db_fav = make_unique<dbFavouritesManager>(&database);
    db_user = make_unique<dbUserManager>(&database);
}

bool Engine::doRegistration(shared_ptr<User> user) {

    if( db_user->access_reg(user->get_email(),user->get_psw(),1)){
        db_user->set_user(user);
        db_user->add_to_db();
        return true;
    }else
        return false;
}

bool Engine::doLogin(const string &email, const string &psw) {
    cout<< "ciao"<<endl;
    if(db_user->access_reg(email, psw, 0)) {
        cout<< "username"<<endl;
        string username = db_user->select_username(email);

        string type = db_user->select_type(email);

        if(type == "C") {

            user = make_shared<Client>();
            db_user->set_user(user);
            db_user->select_data(username);

            // cambiare set_cart in set_user e passare user
            // così anche per set_favourites
            // vedi db_order
            db_cart->set_user(user);
            db_cart->select();

            db_fav->set_user(user);
            db_fav->select();

            db_order->set_user(user);
            db_order->select_for_client();

        } else {
            user = make_unique<Provider>(user->get_db_id(), user->get_type(),user->get_bus_name(),user->get_address(),user->get_email(),user->get_psw(),user->get_username(),user->get_city());


            db_store->set_user(user);
            db_store->select_for_prov(username);

            db_order->set_user(user);
            db_order->select_for_provider();

        }
        return true;
    } else
        return false;
}


