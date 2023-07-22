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

    ~Client() override ;

    shared_ptr<OrdersList> get_order() override {
        return order;
    };

    shared_ptr<Favourites> get_fav() override {
        return fav;
    };

    shared_ptr<Cart> get_cart() override {
        return cart;
    };

    void set_order(OrdersList *ord) override {
        order = ord;
    }

    void set_favourites( std::unique_ptr<Favourites> f) override {
        fav = f;
    }

    void set_cart(Cart *crt) override {
        cart = crt;
    }

    //TODO implementa
    void do_order(OrdersList *ord);

private:
    shared_ptr<OrdersList> order;
    shared_ptr<Favourites> fav;
    shared_ptr<Cart> cart;

    //unique_ptr<Product> prod;
};


#endif //INGROSSO_ONLINE_CLIENT_H
