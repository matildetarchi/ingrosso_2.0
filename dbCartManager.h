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

    //methods

    void add_to_db(Cart *cart);
    void remove_all(const string &username);
    void remove_prod(int id);
    int select_count(const string &username);
    void select(const string &username);

};


#endif //INGROSSO_ONLINE_DBCARTMANAGER_H
