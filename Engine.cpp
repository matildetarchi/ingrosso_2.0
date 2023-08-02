//
// Created by dario on 16/06/2023.
//

#include "Engine.h"

Engine::Engine() {

    database=new SQLite::Database("ingrossodb.sqlite");
    db_cart = make_unique<dbCartManager>(database);
    db_store = make_unique<dbStoreManager>(database);
    db_order = make_unique<dbOrdersManager>(database);
    db_fav = make_unique<dbFavouritesManager>(database);
}

bool Engine::doRegistration(User *user) {

    if( db_user->access_reg(user->get_email(),user->get_psw(),1)){
        db_user->set_user(user);
        db_user->add_to_db();
        return true;
    }else
        return false;
}

bool Engine::doLogin(const string &email, const string &psw) {
    if(db_user->access_reg(email, psw, 0)) {
        string username = db_user->select_username(email);
        string type = db_user->select_type(email);

        if(type == "C") {

            user = make_shared<Client>();
            db_user->set_user(user);
            db_user->select_data(username);

            // cambiare set_cart in set_user e passare user
            // così anche per set_favourites
            // vedi db_order
            db_cart->set_cart(user->get_cart());
            db_cart->select(username);

            db_fav->set_favourites(user->get_fav());
            db_fav->select(username);

            db_order->set_user(user);
            db_order->select_for_client(username);
        } else {
            user = make_unique<Provider>(user->get_type(),user->get_bus_name(),user->get_address(),user->get_email(),user->get_psw(),user->get_username(),user->get_city());

            db_store->set_store(user->get_store());
            db_store->select_for_prov(username);

            db_order->set_orders(user->get_order());
            db_order->select_for_provider(username);
        }
        return true;
    } else
        return false;
}


