//
// Created by Andrea Lipperi on 15/06/23.
//

#ifndef INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
#define INGROSSO_ONLINE_DBFAVOURITESMANAGER_H


#include "Database.h"
#include <SQLiteCpp/Database.h>
#include <memory>
#include <utility>
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <string>

#include "User.h"


using namespace std;
class dbFavouritesManager {
public:

    explicit dbFavouritesManager(shared_ptr<Database> d);



    void set_user(shared_ptr<User> o){
        user = std::move(o);

    }
    void add_to_db();
    void remove_all();
    void remove_prod(int id);
    void select();

private:

    shared_ptr<Favourites> fav;

    shared_ptr<SQLite::Database> db;
    shared_ptr<Product> prod;
    shared_ptr<User> user;
};


#endif //INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
