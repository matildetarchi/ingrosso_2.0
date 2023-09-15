//
// Created by dario on 15/06/2023.
//

#ifndef INGROSSO_ONLINE_DBORDERSMANAGER_H
#define INGROSSO_ONLINE_DBORDERSMANAGER_H
#include "store.h"
#include <string>
#include <utility>
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <SQLiteCpp/Database.h>
#include "OrdersList.h"
#include "Order.h"
#include "Product.h"
#include "User.h"
#include <memory>
#include "Database.h"
#include <stdexcept>


class dbOrdersManager {

public:


    explicit dbOrdersManager(const shared_ptr<Database>& d);


    void set_user(shared_ptr<User> o){
        user = std::move(o);
    }

    void add_to_db();

    void change_status(const string &new_status, int id_order);

    void cancel_order(int id_order);

    void select_for_provider();

    void select_for_client();

    int select_id_last_order(const string &username_prov);
    int select_count_for_provider();
    int select_count_for_client();


private:
    shared_ptr<OrdersList> tab_order;
    shared_ptr<SQLite::Database> db;
    shared_ptr<Product> prod;
    shared_ptr<User> user;
    shared_ptr<Order> order;
    shared_ptr<Date> date;
    vector<shared_ptr<Order>> ord_list;
};


#endif //INGROSSO_ONLINE_DBORDERSMANAGER_H
