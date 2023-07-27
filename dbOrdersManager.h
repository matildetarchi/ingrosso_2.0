//
// Created by dario on 15/06/2023.
//

#ifndef INGROSSO_ONLINE_DBORDERSMANAGER_H
#define INGROSSO_ONLINE_DBORDERSMANAGER_H
#include "Store.h"
#include <string>
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include "Database.h"
#include "OrdersList.h"
#include "Product.h"
#include <memory>

class dbOrdersManager {

public:
    dbOrdersManager(SQLite::Database* d);

    void set_orders(std::shared_ptr<OrdersList> o){
        tab_order = o;
    }

    void add_to_db();

    void changeStatus(const string &username,int id_single_order,const string &new_status);

    void cancel_order(const string &username, int id_single_order, const string &us_prov);

    void select_for_provider(const string &username);

    void select_for_client(const string &username);

    int select_id_last_order(const string &username_prov);

private:
    shared_ptr<OrdersList> tab_order;
    SQLite::Database *db;
    unique_ptr<Product> prod;
    shared_ptr<Order> order;
};


#endif //INGROSSO_ONLINE_DBORDERSMANAGER_H
