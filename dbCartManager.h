//
// Created by Andrea Lipperi on 15/06/23.
//

#ifndef INGROSSO_ONLINE_DBCARTMANAGER_H
#define INGROSSO_ONLINE_DBCARTMANAGER_H


#include "database.h"
#include "cart.h"
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <string>


using namespace std;

class dbCartManager {
public:
    dbCartManager(SQLite::Database* d);


    void set_cart(Cart* c){
        cart=c;
    }

    void add_to_db();
    void remove_all(const string &username);
    void remove_prod(int id);
    void select(const string &username);

private:
    Cart *cart;
    SQLite::Database *db;
    Product* prod;
};


#endif //INGROSSO_ONLINE_DBCARTMANAGER_H
