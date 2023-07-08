//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Provider.h"

using namespace std;

Provider::Provider( const string &t, const string &bn,const string &a, const string &e,
                const string &password, const string &us, const string &c) : User(t, bn, a, e, password, us, c), order(nullptr),store(nullptr){}

Provider::~Provider() {
    if(order != nullptr)
        delete order;

    if(store != nullptr)
        delete store;
}

void accept_order(Order* o) {
    int id = 0;
    o->set_status(id, "A");
}

void deny_order(Order* o) {
    int id = 0;
    o->set_status(id, "D");
}

