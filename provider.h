//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_PROVIDER_H
#define INGROSSO_ONLINE_PROVIDER_H

#include "user.h"
#include "OrdersList.h"
#include "cart.h"


class Provider: public User {
public:
    Provider();
    Provider( const std::string &t, const std::string &bn,const std::string &a, const std::string &e, const std::string &password, const std::string &us, const std::string &c);
    ~Provider() override;

    const Orders *getOrder();
    const Store *getStore();

    void setOrder(Orders *ord) override;
    void setStore(Store *st) override;

private:
    Orders *order;
    Store *store;
};



#endif //INGROSSO_ONLINE_PROVIDER_H
