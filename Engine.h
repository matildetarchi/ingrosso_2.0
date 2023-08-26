//
// Created by dario on 16/06/2023.
//

#ifndef INGROSSO_ONLINE_ENGINE_H
#define INGROSSO_ONLINE_ENGINE_H
#include "User.h"
#include "OrdersList.h"
#include "store.h"
#include "favourites.h"
#include "cart.h"
#include "Client.h"
#include "Provider.h"
#include "dbCartManager.h"
#include "dbFavouritesManager.h"
#include "dbOrdersManager.h"
#include "dbStoreManager.h"
#include "dbUserManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <SQLiteCpp/Database.h>


class Engine {
public:
    Engine();


    bool do_registration(shared_ptr <User> user);
    bool do_login(const string &email, const string &psw);

    shared_ptr<User> get_user() {
        return user;
    }
    shared_ptr<dbCartManager> get_db_cart() {
        return db_cart;
    }
    shared_ptr<dbOrdersManager> get_db_order() {
        return db_order;
    }
    shared_ptr<dbStoreManager> get_db_store() {
        return db_store;
    }
    shared_ptr<dbFavouritesManager> get_db_fav() {
        return db_fav;
    }
    shared_ptr<dbUserManager> get_db_user() {
        return db_user;
    }
private:
    shared_ptr<User> user;
    shared_ptr<dbCartManager> db_cart;
    shared_ptr<dbOrdersManager> db_order;
    shared_ptr<dbStoreManager> db_store;
    shared_ptr<dbFavouritesManager> db_fav;
    shared_ptr<dbUserManager> db_user;
    SQLite::Database *database;



};


#endif //INGROSSO_ONLINE_ENGINE_H
