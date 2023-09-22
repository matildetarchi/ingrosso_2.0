//
// Created by dario on 15/06/2023.
//

#ifndef INGROSSO_ONLINE_DBSTOREMANAGER_H
#define INGROSSO_ONLINE_DBSTOREMANAGER_H

#include "dbCartManager.h"
#include "dbFavouritesManager.h"
#include "Provider.h"


class dbStoreManager {
public:
    explicit dbStoreManager(const shared_ptr<Database>& d);


    void set_user(shared_ptr<Provider> o){
        prov = std::move(o);
    }

    void set_store() {
        st = prov->get_store();
    }
    void set_prod_list(){
        prod_list = st->get_products();
    }

    void add_to_db();
    bool remove_from_db(int id_store);
    void change_data(int index, const string& desc_prod, double price, int quantity);
    vector<shared_ptr<Product>> select_for_client(const string &sub_name, const string &disp);
    void select_for_prov();
    int select_count_for_client(const string &sub_name, const string &disp);
    int select_count_for_provider();
    shared_ptr<Product> select_prod_to_modify(int id_prod);
private:

    shared_ptr<Store> st;
    vector<shared_ptr<Product>> prod_list;
    shared_ptr<SQLite::Database> db;
    shared_ptr<Product> prod;
    shared_ptr<Provider> prov;
};


#endif //INGROSSO_ONLINE_DBSTOREMANAGER_H
