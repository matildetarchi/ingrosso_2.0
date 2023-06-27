//
// Created by Matilde Tarchi on 16/06/23.
//

#include "provider.h"

Provider::Provider( const std::string &t, const std::string &bn,const std::string &a, const std::string &e,
                const std::string &password, const std::string &us, const std::string &c) : User(t, bn, a, e, password, us, c), order(nullptr),store(nullptr){}

Provider::~Provider() {
    if(order != nullptr)
        delete order;

    if(store != nullptr)
        delete store;
}
const OrdersList* Provider::get_order() {
    return order;
}

void Provider::set_order(OrdersList *ord) {
    order = ord;
}

const Store *Provider::get_store() {
    return store;
}

void Provider::set_store(Store *st) {
    store=st;
}

