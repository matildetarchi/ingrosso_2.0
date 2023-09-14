//
// Created by Andrea Lipperi on 15/06/23.
//

#ifndef INGROSSO_ONLINE_DBCARTMANAGER_H
#define INGROSSO_ONLINE_DBCARTMANAGER_H


#include "Database.h"
#include "SQLiteCpp/Database.h"
#include "cart.h"
#include <utility>
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <string>
#include <memory>
#include "User.h"


using namespace std;

class dbCartManager {
public:
    explicit dbCartManager(const shared_ptr<Database>& d);


    void set_user(shared_ptr<User> o){
        user = std::move(o);
    }


    void add_to_db();
    void remove_all();
    void remove_prod(int id);
    void select();
    int select_count_of_prod();

private:

    shared_ptr<Cart> cart;
    shared_ptr<SQLite::Database> db;
    shared_ptr<Product> prod;
    shared_ptr<User> user;

};


#endif //INGROSSO_ONLINE_DBCARTMANAGER_H
