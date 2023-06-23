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
    //methods

    void add_to_db(Cart *cart);
    void remove_all(const string &username);
    void remove_prod(int id);
    Cart select(const string &username);

private:
    Cart *cart;
};


#endif //INGROSSO_ONLINE_DBCARTMANAGER_H
