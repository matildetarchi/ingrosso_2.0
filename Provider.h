//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_PROVIDER_H
#define INGROSSO_ONLINE_PROVIDER_H

#include "User.h"
#include "OrdersList.h"
#include "Cart.h"
#include "OrderProduct.h"

using namespace std;
class Provider: public User {
public:

    Provider( const string &t, const string &bn,const string &a, const string &e, const string &password, const string &us, const string &c);
    ~Provider() override;

     OrdersList *get_order()override {
           return order;
     }

     Store *get_store()override {
         return store;
     }

    void set_order(OrdersList *ord) override {
        order = ord;
    }

    void set_store(Store *st) override {
        store=st;
    }

    void accept_order(Order* o);

    void deny_order(Order* o);

private:
    OrdersList *order;
    Store *store;
};



#endif //INGROSSO_ONLINE_PROVIDER_H
