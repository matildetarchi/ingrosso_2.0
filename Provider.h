//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_PROVIDER_H
#define INGROSSO_ONLINE_PROVIDER_H

#include "User.h"
#include "OrdersList.h"
#include "Cart.h"
#include "OrderProduct.h"
#include <memory>

using namespace std;
class Provider: public User {
public:

    Provider( const string &t, const string &bn,const string &a, const string &e, const string &password, const string &us, const string &c);
    ~Provider() override;

    shared_ptr<OrdersList> get_orderList()override {
           return order;
    }


    shared_ptr<Store> get_store()override {
         return store;
    }

    void set_order(OrdersList *ord) override {
        order = ord;
    }

    void set_store(Store *st) override {
        store=st;
    }
    //TODO implementa
    void accept_order(int index);
    //dentro prendo l'ordine all'index passato

    void delete_order(int index);

private:
    shared_ptr<OrdersList> order;
    shared_ptr<Store> store;
};



#endif //INGROSSO_ONLINE_PROVIDER_H
