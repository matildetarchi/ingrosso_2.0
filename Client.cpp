//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Client.h"

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
