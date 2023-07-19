//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_ORDERSLIST_H
#define INGROSSO_ONLINE_ORDERSLIST_H

#define add 0
#define cancel 1
#include "Store.h"
#include <iostream>
#include <string>
#include <vector>
#include "Order.h"

using namespace std;

class OrdersList{
public:

    OrdersList(const string &user);

    ~OrdersList();


    int get_num_prod() const {
        return num_prod;
    }

    const string &get_username_user() {
        return username_user;
    };

    void add_order( const string &status, Date *date_order, const string &username_other, int id_s_order);
    void update_num(int control);
    void remove_one(int index);
    void remove_all();

    vector<Order*> get_orders(){
        return orders;
    };


private:
    string username_user;
    int num_prod{};
    vector<Order*> orders;

};

#endif // INGROSSO_ONLINE_ORDERSLIST_H