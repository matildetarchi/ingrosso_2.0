//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_CLIENT_H
#define INGROSSO_ONLINE_CLIENT_H

#include "User.h"
#include "OrdersList.h"
#include "Favourites.h"
#include "Cart.h"


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

    void set_order(OrdersList *ord) override {
        order = ord;
    }
    void set_favourites(Favourites *f) override {
        fav=f;
    }
    void set_cart(Cart *crt) override {
        cart=crt;
    }

private:
    OrdersList *order;
    Favourites *fav;
    Cart *cart;
};


#endif //INGROSSO_ONLINE_CLIENT_H
