//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_PROVIDER_H
#define INGROSSO_ONLINE_PROVIDER_H

#include "User.h"
#include "OrdersList.h"
#include "Cart.h"

#include <memory>

using namespace std;
class Provider: public User {
public:

    Provider(int id, const string &t, const string &bn,const string &a, const string &e, const string &password, const string &us, const string &c);
    ~Provider() override;


    shared_ptr<OrdersList> get_order()override {

           return order;
    }


    shared_ptr<Store> get_store()override {
         return store;
    }


    void set_order(shared_ptr<OrdersList> ord) override {
        order = ord;
    }

    void set_store(shared_ptr<Store> st) override {
        store = st;

    }

    void accept_order(std::shared_ptr<Order> o);


    void denied_order(std::shared_ptr<Order> o);

private:
    shared_ptr<OrdersList> order;
    shared_ptr<Store> store;
};



#endif //INGROSSO_ONLINE_PROVIDER_H
