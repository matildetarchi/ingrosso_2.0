//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_CLIENT_H
#define INGROSSO_ONLINE_CLIENT_H

#include "User.h"
#include "OrdersList.h"
#include "Favourites.h"
#include "Cart.h"
#include <memory>

using namespace std;

class Client : public User {
public:

    Client(const string &t, const string &bn, const string &a, const string &e, const string &password,
           const string &us, const string &c);

    ~Client() override;

    //TODO capire se serve davvero override, perche teoricamente servirebbe se la funzione è presente anche nella classe base
    OrdersList *get_order() override {
        return order;
    };

    Favourites *get_fav() override {
        return fav;
    };

    Cart *get_cart() override {
        return cart;
    };

    void set_order(OrdersList *ord) override {
        order = ord;
    }

    void set_favourites(Favourites *f) override {
        fav = f;
    }

    void set_cart(Cart *crt) override {
        cart = crt;
    }

    void do_order(OrdersList *ord);

private:
    //TODO vedere se va bene utilizzare unique pointer in questo punto
    OrdersList *order;
    Favourites *fav;
    Cart *cart;
};


#endif //INGROSSO_ONLINE_CLIENT_H
