//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_CLIENT_H
#define INGROSSO_ONLINE_CLIENT_H

#include "User.h"
#include "OrdersList.h"
#include "favourites.h"
#include "cart.h"
#include <memory>

using namespace std;

class Client : public User {
public:

    Client();
    Client(int id, const string &t, const string &bn, const string &a, const string &e, const string &password,
           const string &us, const string &c);

    ~Client() override ;






    /*void set_order( shared_ptr<OrdersList> ord) override {
        order = ord;
    }

    void set_favourites( shared_ptr<Favourites> f) override {
        fav = f;
    }

    void set_cart( shared_ptr<Cart> crt) override {
        cart = crt;
    }*/


    void do_order(shared_ptr<Order> o);
    void add_to_cart(shared_ptr<Product> p);
    void add_to_fav(shared_ptr<Product> p);

private:

    shared_ptr<OrdersList> order;
    shared_ptr<Favourites> fav;
    shared_ptr<Cart> cart;

    shared_ptr<Product> prod;
};


#endif //INGROSSO_ONLINE_CLIENT_H
