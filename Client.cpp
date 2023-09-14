//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Client.h"

#include <utility>
using namespace std;

Client::Client() : User(){}

Client::Client( const string &t, const string &bn,const string &a, const string &e,
               const string &password, const string &us, const string &c) : User(t, bn, a, e, password, us, c){

    cart = make_unique<Cart>(us);
    order = make_unique<OrdersList>(us);
    fav = make_unique<Favourites>(us);
}

Client::~Client() {

}

void Client::do_order(const shared_ptr<Order>& o) {
    order->add_order(o);

}

void Client::add_to_cart(shared_ptr<Product> p) {

    cart->add_product(std::move(p));

}

void Client::add_to_fav(shared_ptr<Product> p) {
    fav->add_product(std::move(p));
}


