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


    bool doRegistration(shared_ptr <User> user);
    bool doLogin(const string &email, const string &psw);

    shared_ptr<User> get_user() {
        return user;
    }

private:
    shared_ptr<User> user;
    unique_ptr<dbCartManager> db_cart;
    unique_ptr<dbOrdersManager> db_order;
    unique_ptr<dbStoreManager> db_store;
    unique_ptr<dbFavouritesManager> db_fav;
    unique_ptr<dbUserManager> db_user;



};


#endif //INGROSSO_ONLINE_ENGINE_H
