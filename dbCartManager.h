//
// Created by Andrea Lipperi on 15/06/23.
//

#ifndef INGROSSO_ONLINE_DBCARTMANAGER_H
#define INGROSSO_ONLINE_DBCARTMANAGER_H


#include "Client.h"
#include "Database.h"


using namespace std;


class dbCartManager {
public:
    explicit dbCartManager(const shared_ptr<Database>& d);


    void set_user(shared_ptr<Client> o){
        client = std::move(o);
    }
    void set_cart(){
        cart = client->get_cart();
    }


    void add_to_db();
    void remove_all();
    void remove_prod(int id);
    void select();
    int select_count_of_prod();

private:

    shared_ptr<Cart> cart;
    shared_ptr<SQLite::Database> db;
    shared_ptr<Product> prod;
    shared_ptr<Client> client;
    vector<shared_ptr<Product>> prod_list;

};


#endif //INGROSSO_ONLINE_DBCARTMANAGER_H