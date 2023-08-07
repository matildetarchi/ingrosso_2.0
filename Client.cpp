//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Client.h"
using namespace std;

Client::Client() : User(){}

Client::Client(int id, const string &t, const string &bn,const string &a, const string &e,
               const string &password, const string &us, const string &c) : User(id, t, bn, a, e, password, us, c){

    cart = make_unique<Cart>(us);
    order = make_unique<OrdersList>(us);
    fav = make_unique<Favourites>(us);
}

Client::~Client() {

}

void Client::do_order(OrdersList *order) {

}
