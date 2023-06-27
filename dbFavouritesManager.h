//
// Created by Andrea Lipperi on 15/06/23.
//

#ifndef INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
#define INGROSSO_ONLINE_DBFAVOURITESMANAGER_H


#include "Database.h"
#include "Favourites.h"
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <string>

using namespace std;
class dbFavouritesManager {
public:

    dbFavouritesManager(SQLite::Database* d);


    void set_favourites(Favourites* f){
        fav=f;
    }
    void add_to_db();
    void remove_all(const string &username);
    void remove_prod(int id);
    void select(const string username);

private:
    Favourites *fav;
    SQLite::Database *db;
    Product* prod;
};


#endif //INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
