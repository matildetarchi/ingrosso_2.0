//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_ORDERSLIST_H
#define INGROSSO_ONLINE_ORDERSLIST_H

#define add 0
#define cancel 1
#include "Store.h"
#include <string>
#include <vector>
#include "Order.h"

using namespace std;

class OrdersList{
public:
    OrdersList();
    OrdersList(const string &user);

    ~OrdersList();


    int get_num_prod(){
        return num_prod;
    }

    const string get_username_user(){
        return username_user;
    };

    void add_order(Product* p, string status, string date_order, string username_other, int id_order);
    void update_num(int control);
    void remove_one(int index);
    void remove_all();

    vector<Order*> orders;

private:
    string username_user;
    int num_prod;
};

#endif // INGROSSO_ONLINE_ORDERSLIST_H