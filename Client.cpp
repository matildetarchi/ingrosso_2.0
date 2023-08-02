//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Client.h"
using namespace std;

Client::Client() : User(){}

Client::Client( const string &t, const string &bn,const string &a, const string &e,
               const string &password, const string &us, const string &c) : User(t, bn, a, e, password, us, c){

    cart = make_shared<Cart>(us);
    order = make_shared<OrdersList>(us);
    fav = make_shared<Favourites>(us);
}

Client::~Client() {

}

void Client::do_order(OrdersList *order) {

}
