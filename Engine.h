//
// Created by dario on 16/06/2023.
//

#ifndef INGROSSO_ONLINE_ENGINE_H
#define INGROSSO_ONLINE_ENGINE_H
#include "User.h"
#include "Database.h"
#include "OrdersList.h"
#include "Store.h"
#include "Favourites.h"
#include "Cart.h"
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
    SQLite::Database *database;
    dbCartManager *db_cart;
    dbOrdersManager *db_order;
    dbStoreManager *db_store;
    dbFavouritesManager *db_fav;
    dbUserManager *db_user;



};


#endif //INGROSSO_ONLINE_ENGINE_H