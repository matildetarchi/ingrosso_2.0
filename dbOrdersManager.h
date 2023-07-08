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
#include "OrderProduct.h"

class dbOrdersManager {

public:
    dbOrdersManager(SQLite::Database* d);

    void set_orders(OrdersList* o){
        tab_order=o;
    }

    void add_to_db();

    void changeStatus(const string username,int cod_order,const string new_status);

    void cancel_order(const std::string username, int cod_order, const string us_prov);

    void select_for_provider(const string username);

    void select_for_client(const string username);

    int select_id_last_order(const string username_prov);

private:
    OrdersList *tab_order;
    SQLite::Database *db;
    OrderProduct *order;
    Product* prod;
};


#endif //INGROSSO_ONLINE_DBORDERSMANAGER_H
