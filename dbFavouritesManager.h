//
// Created by Andrea Lipperi on 15/06/23.
//

#ifndef INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
#define INGROSSO_ONLINE_DBFAVOURITESMANAGER_H


#include "database.h"
#include "favourites.h"
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <string>

using namespace std;
class dbFavouritesManager {
public:
    //methods
    void add_to_db(Favourites *new_fav);
    void remove_prod(int id);
    void select(const string &username);

private:
    Favourites *fav;
};


#endif //INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
