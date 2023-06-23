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
        Favourites fav_vect;
        Cart cart_vect;
        Orders ord_vect;
        Store store_vect;
        //TODO controllare quello che passa tra parentesi ( domanda caro) (voglio sapere se passa quello creato o uno a caso)
        if(user->get_type() == "C") {

            fav_vect=db_fav->select(username);
            cart_vect=db_cart->select(username);
            ord_vect=db_order->select_for_client(username);
            user = new Client(user->get_type(),user->get_bus_name(),user->get_address(),user->get_email(),user->get_psw(),user->get_username(),user->get_city());
            user->setOrder(&ord_vect);
            user->setCart(&cart_vect);
            user->setFavourites(&fav_vect);
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


