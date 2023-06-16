//
// Created by dario on 15/06/2023.
//

#ifndef INGROSSO_ONLINE_DBORDERSMANAGER_H
#define INGROSSO_ONLINE_DBORDERSMANAGER_H
#include "store.h"
#include <string>
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include "database.h"
#include "orders.h"

class dbOrdersManager {

public:
    void add_to_db(Orders *orders);

    void changeStatus(const string& username,const string &cod_order,const string &new_status);

    void cancel_order(const std::string &username, const std::string &cod_order, const string &us_prov);

    void select_for_provider(const string &username, int control);

    void select_for_client(const string &username, int control);

    int select_id_last_order(const string &username_prov);

private:
    Orders tab_order;
};


#endif //INGROSSO_ONLINE_DBORDERSMANAGER_H
