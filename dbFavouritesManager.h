//
// Created by Andrea Lipperi on 15/06/23.
//

#ifndef INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
#define INGROSSO_ONLINE_DBFAVOURITESMANAGER_H

#include "Client.h"
#include "Database.h"





using namespace std;
class dbFavouritesManager {
public:

    explicit dbFavouritesManager(shared_ptr<Database> d);



    void set_user(shared_ptr<Client> o){
        client = std::move(o);
    }

    void add_to_db();
    void remove_all();
    void remove_prod(int id);
    void select();
    int select_count_of_prod();

private:

    shared_ptr<Favourites> fav;

    shared_ptr<SQLite::Database> db;
    shared_ptr<Product> prod;
    shared_ptr<Client> client;
    vector<std::shared_ptr<Product>> prod_list;
};


#endif //INGROSSO_ONLINE_DBFAVOURITESMANAGER_H
