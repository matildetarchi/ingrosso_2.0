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
#include "User.h"
#include <memory>

class dbOrdersManager {

public:
    dbOrdersManager(SQLite::Database* d);

    void set_user(shared_ptr<User> o){
        user = o;
    }

    void add_to_db();

    void changeStatus(const string &username,const string &new_status, int id_order);

    void cancel_order(const string &username, int id_single_order, const string &us_prov);

    void select_for_provider();

    void select_for_client();

    int select_id_last_order(const string &username_prov);

private:
    shared_ptr<OrdersList> tab_order;
    SQLite::Database *db;
    shared_ptr<Product> prod;
    shared_ptr<User> user;
};


#endif //INGROSSO_ONLINE_DBORDERSMANAGER_H
