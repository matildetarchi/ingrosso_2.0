//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_CLIENT_H
#define INGROSSO_ONLINE_CLIENT_H

#include "user.h"
#include "OrdersList.h"
#include "favourites.h"
#include "cart.h"


class Client:public User {
public:
    Client();
    Client( const std::string &t, const std::string &bn,const std::string &a, const std::string &e, const std::string &password, const std::string &us, const std::string &c);
    ~Client() override;

    OrdersList *get_order()override{
        return order;
    };
    Favourites *get_fav()override{
        return fav;
    };
    Cart *get_cart()override{
        return cart;
    };

    void set_order(OrdersList *ord) override;
    void set_favourites(Favourites *f) override;
    void set_cart(Cart *crt) override;

private:
    OrdersList *order;
    Favourites *fav;
    Cart *cart;
};


#endif //INGROSSO_ONLINE_CLIENT_H
