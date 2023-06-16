//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_PROVIDER_H
#define INGROSSO_ONLINE_PROVIDER_H

#include "user.h"
#include "orders.h"
#include "cart.h"


class Provider: public User {
public:
    Provider();
    Provider( const std::string &t, const std::string &bn,const std::string &a, const std::string &e, const std::string &password, const std::string &us, const std::string &c);
    virtual ~Provider();

    Orders *getOrder();
    Store *getStore();

    void setOrder(Orders *ord);
    void setStore(Store *st);

private:
    Orders *order;
    Store *store;
};



#endif //INGROSSO_ONLINE_PROVIDER_H
