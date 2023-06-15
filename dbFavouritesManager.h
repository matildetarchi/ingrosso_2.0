//
// Created by Andrea Lipperi on 15/06/23.
//

#ifndef INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
#define INGROSSO_ONLINE_DBFAVOURITESMANAGER_H


#include "database.h"
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <string>

using namespace std;
class dbFavouritesManager {
//methods

    void add_to_db();
    void remove_prod(int id);
    void select(const string &username);
    int select_count(const string &username);
};


#endif //INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
