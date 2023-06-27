//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_PROVIDER_H
#define INGROSSO_ONLINE_PROVIDER_H

#include "User.h"
#include "OrdersList.h"
#include "Cart.h"


class Provider: public User {
public:
    Provider();
    Provider( const std::string &t, const std::string &bn,const std::string &a, const std::string &e, const std::string &password, const std::string &us, const std::string &c);
    ~Provider() override;

     OrdersList *get_order()override{
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
private:
    OrdersList *order;
    Store *store;
};



#endif //INGROSSO_ONLINE_PROVIDER_H
