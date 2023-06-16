//
// Created by dario on 16/06/2023.
//

#include "engine.h"

Engine::Engine() {}

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
        //TODO controllare quello che passa tra parentesi ( domanda caro) (voglio sapere se passa quello creato o uno a caso)
        if(user->get_type() == "C") {
            db_fav->select(username);
            db_cart->select(username);
            db_order->select_for_client(username);
            user = new Client(user->get_type(),user->get_bus_name(),user->get_address(),user->get_email(),user->get_psw(),user->get_username(),user->get_city());
            user->setOrder(order);
            user->setCart(cart);
            user->setFavourites(favourite);
        } else {
            db_order->select_for_provider(username);
            db_store->select_for_prov(username);
            user = new Provider(user->get_type(),user->get_bus_name(),user->get_address(),user->get_email(),user->get_psw(),user->get_username(),user->get_city());
            user->setOrder(order);
            user->setStore(store);
        }
        return true;
    } else
        return false;
}


