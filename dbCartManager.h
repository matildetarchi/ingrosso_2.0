//
// Created by Andrea Lipperi on 15/06/23.
//

#ifndef INGROSSO_ONLINE_DBCARTMANAGER_H
#define INGROSSO_ONLINE_DBCARTMANAGER_H


#include "Database.h"
#include "Cart.h"
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <string>
#include <memory>


using namespace std;

class dbCartManager {
public:
    dbCartManager(SQLite::Database* d);


    void set_cart(shared_ptr<Cart> c){
        cart = c;
    }


    void add_to_db();
    void remove_all(const string &username);
    void remove_prod(int id);
    void select(const string &username);

private:

    shared_ptr<Cart> cart;
    SQLite::Database *db;
    unique_ptr<Product> prod;
};


#endif //INGROSSO_ONLINE_DBCARTMANAGER_H
