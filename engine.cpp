//
// Created by dario on 16/06/2023.
//

#include "engine.h"

Engine::Engine() {
    database=new SQLite::Database("ingrossodb.sqlite");
    db_cart=new dbCartManager(database);
    db_store=new dbStoreManager(database);
    db_order=new dbOrdersManager(database);
    db_fav=new dbFavouritesManager(database);
}

bool Engine::doRegistration(User *user) {

    if( db_user->access_reg(user->get_email(),user->get_psw(),1)){
        db_user->add_to_db(user);
        return true;
    }else
        return false;
}

bool Engine::doLogin(const string &email, const string &psw) {
    if(db_user->access_reg(email, psw, 0)) {
        string username = db_user->select_username(email);
        db_user->select_data(username);

        if(user->get_type() == "C") {

            user = new Client(user->get_type(),user->get_bus_name(),user->get_address(),user->get_email(),user->get_psw(),user->get_username(),user->get_city());
            db_cart->set_cart(user->get_cart());
            db_cart->select(username);
            db_fav->set_favourites(user->get_fav());
            db_fav->select(username);
            db_order->set_orders(user->get_order());
            db_order->select(username);
        } else {
            ord_vect=db_order->select_for_provider(username);
            store_vect=db_store->select_for_prov(username);
            user = new Provider(user->get_type(),user->get_bus_name(),user->get_address(),user->get_email(),user->get_psw(),user->get_username(),user->get_city());
            user->setOrder(&ord_vect);
            user->setStore(&store_vect);
        }
        return true;
    } else
        return false;
}


