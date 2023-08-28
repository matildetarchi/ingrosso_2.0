//
// Created by dario on 15/06/2023.
//

#ifndef INGROSSO_ONLINE_DBSTOREMANAGER_H
#define INGROSSO_ONLINE_DBSTOREMANAGER_H
#include <iostream>
#include "store.h"
#include <SQLiteCpp/Database.h>
#include <vector>
#include <string>
#include <SQLiteCpp/Statement.h>
#include "dbCartManager.h"
#include "dbFavouritesManager.h"
#include "User.h"
#include <memory>
#include "Database.h"
#include <stdexcept>


class dbStoreManager {
public:
    explicit dbStoreManager(shared_ptr<Database> d);


    void set_user(shared_ptr<User> o){
        user = std::move(o);
    }

    void add_to_db();
    bool remove_from_db(int id_store);
    void change_data(int index, const string& desc_prod, double price, int quantity);
    vector<vector<string>> select_for_client(const string &sub_name, const string &disp, const string &order="store.id");
    void select_for_prov();
    int select_count_for_client(const string &sub_name, const string &disp);
    int select_count_for_provider();
    shared_ptr<Product> select_prod_to_modify(int id_prod);
private:

    shared_ptr<Store> st;

    shared_ptr<SQLite::Database> db;
    shared_ptr<Product> prod;
    dbFavouritesManager* fav;
    dbCartManager* cart;
    shared_ptr<User> user;
};


#endif //INGROSSO_ONLINE_DBSTOREMANAGER_H
