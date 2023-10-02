//
// Created by dario on 15/06/2023.
//

#ifndef INGROSSO_ONLINE_DBORDERSMANAGER_H
#define INGROSSO_ONLINE_DBORDERSMANAGER_H

#include "Database.h"
#include <stdexcept>
#include "User.h"



class dbOrdersManager {

public:

    explicit dbOrdersManager(const shared_ptr<Database>& d);


    void set_user(const shared_ptr<User>& u){
       user = u;
    }

    void set_orderlist(){
        tab_order= user->get_order_list();
    }

    void add_to_db();
    void change_status(const string &new_status, int id_order);
    void cancel_order(int id_order);
    void select_for_provider();
    void select_for_client();
    int select_count_for_provider_onlyp(int control);
    int select_count_for_provider();
    int select_count_for_client_onlyp();
    int select_count_for_client();




private:
    shared_ptr<OrdersList> tab_order;
    shared_ptr<SQLite::Database> db;
    shared_ptr<Product> prod;
    shared_ptr<Order> order;
    shared_ptr<Date> date;
    vector<shared_ptr<Order>> ord_list;
    shared_ptr<User> user;
};


#endif //INGROSSO_ONLINE_DBORDERSMANAGER_H
