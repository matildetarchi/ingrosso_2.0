//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_ORDERSLIST_H
#define INGROSSO_ONLINE_ORDERSLIST_H

#define put_in 0
#define cc 1
#include "Store.h"
#include "Order.h"

using namespace std;

class OrdersList{
public:
    OrdersList();
    explicit OrdersList(string user);

    ~OrdersList();


    [[nodiscard]] int get_num_order() const  {
        return num_order;
    }

    vector<shared_ptr<Order>> get_orders(){
        return orders;
    }

    void add_order( const shared_ptr<Order>& ord);
    void update_num(int control);
    void remove_one(int index);
    void remove_all();
    bool modify_status(int id_order, const string &new_status);


private:
    string username_user;
    int num_order;
    vector<shared_ptr<Order>> orders;


};

#endif // INGROSSO_ONLINE_ORDERSLIST_H