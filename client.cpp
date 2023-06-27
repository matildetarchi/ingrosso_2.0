//
// Created by Matilde Tarchi on 16/06/23.
//

#include "client.h"

Client::Client( const std::string &t, const std::string &bn,const std::string &a, const std::string &e,
               const std::string &password, const std::string &us, const std::string &c) : User(t, bn, a, e, password, us, c), order(nullptr), fav(nullptr), cart(nullptr){}

Client::~Client() {
    if(order != nullptr)
        delete order;

    if(fav != nullptr)
        delete fav;

    if(cart != nullptr)
        delete cart;
}



void Client::set_order(OrdersList *ord) {
    order = ord;
}

void Client::set_cart(Cart *crt) {
    cart=crt;
}


void Client::set_favourites(Favourites *f) {
    fav=f;
}
