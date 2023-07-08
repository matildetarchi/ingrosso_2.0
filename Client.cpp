//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Client.h"
using namespace std;

Client::Client( const string &t, const string &bn,const string &a, const string &e,
               const string &password, const string &us, const string &c) : User(t, bn, a, e, password, us, c), order(nullptr), fav(nullptr), cart(nullptr){}

Client::~Client() {
    if(order != nullptr)
        delete order;

    if(fav != nullptr)
        delete fav;

    if(cart != nullptr)
        delete cart;
}

void Client::do_order(OrdersList *order) {

}
