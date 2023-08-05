//
// Created by dario on 15/06/2023.
//

#ifndef INGROSSO_ONLINE_DBSTOREMANAGER_H
#define INGROSSO_ONLINE_DBSTOREMANAGER_H
#include <iostream>
#include "Store.h"
#include "Database.h"
#include <vector>
#include <string>
#include <SQLiteCpp/Statement.h>
#include "dbCartManager.h"
#include "dbFavouritesManager.h"
#include "User.h"

class dbStoreManager {
public:
    dbStoreManager(SQLite::Database* d);

    void set_user(shared_ptr<User> o){
        user = o;
    }

    void add_to_db();
    bool remove_from_db(int id_store);
    void changeData(int index, const string desc_prod, double price, int quantity);
    vector<vector<string>> select_for_client(const string sub_name, const string disp, const string order="store.id");
    void select_for_prov(const string username);
    int select_count_for_client(const string sub_name, const string disp);
    int select_count_for_prov(const string &username);
private:
    Store* st;
    SQLite::Database* db;
    Product* prod;
    dbFavouritesManager* fav;
    dbCartManager* cart;
    shared_ptr<User> user;
};


#endif //INGROSSO_ONLINE_DBSTOREMANAGER_H
