//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Provider.h"

using namespace std;

Provider::Provider( const string &t, const string &bn,const string &a, const string &e,
                const string &password, const string &us, const string &c) : User(t, bn, a, e, password, us, c){

    store = make_shared<Store>(const string &provider);
    order = make_shared<OrdersList>(const string &user);
}

Provider::~Provider() {
    if(order != nullptr)
        delete order;

    if(store != nullptr)
        delete store;
}

void accept_order(std::shared_ptr<Order> o) {
    int id = 0;
    o->set_status(id, "A");
}

void denied_order(std::shared_ptr<Order> o) {
    int id = 0;
    o->set_status(id, "D");
}

