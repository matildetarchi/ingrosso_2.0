//
// Created by dario on 16/06/2023.
//

#ifndef INGROSSO_ONLINE_ENGINE_H
#define INGROSSO_ONLINE_ENGINE_H
#include "user.h"
#include "database.h"
#include "OrdersList.h"
#include "Store.h"
#include "favourites.h"
#include "cart.h"
#include "client.h"
#include "provider.h"
#include "dbCartManager.h"
#include "dbFavouritesManager.h"
#include "dbOrdersManager.h"
#include "dbStoreManager.h"
#include "dbUserManager.h"
#include <string>
#include <iostream>
#include <fstream>


class Engine {
public:
    Engine();

    bool doRegistration(User *user);
    bool doLogin(const string &email, const string &psw);

    User* get_user() {
        return user;
    }
private:
    User *user;
    dbCartManager *db_cart;
    dbOrdersManager *db_order;
    dbStoreManager *db_store;
    dbFavouritesManager *db_fav;
    dbUserManager *db_user;
    SQLite::Database *database;


};


#endif //INGROSSO_ONLINE_ENGINE_H
