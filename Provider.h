//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_PROVIDER_H
#define INGROSSO_ONLINE_PROVIDER_H

#include "User.h"
#include "OrdersList.h"
#include "cart.h"
#include "dbOrdersManager.h"
#include "dbStoreManager.h"
#include <memory>
#include <utility>
#include "Product.h"


using namespace std;
class Provider: public User {
public:
    Provider();
    Provider( const string &t, const string &bn,const string &a, const string &e, const string &password, const string &us, const string &c);
    ~Provider() override;

    void set_db_order(shared_ptr<dbOrdersManager> db_o){
        db_order = std::move(db_o);
    }
    void set_db_store(shared_ptr<dbStoreManager> db_s){
        db_store = std::move(db_s);
    }

    void delete_objects_of_user() override;
    bool  delete_prod (int id_prod);
    void accept_order (int id_order);
    bool modify_prod (int id_store, string desc, double price, int a_q );
    void denied_order(int id_order);
    bool add_prod(const string& desc, double price, int quantity, int a_quantity, const string&  username_prov, const string& sub_category);

private:
    shared_ptr<OrdersList> order;
    shared_ptr<Store> store;
    shared_ptr<dbOrdersManager> db_order;
    shared_ptr<dbStoreManager> db_store;
    shared_ptr<Product> prod;
};



#endif //INGROSSO_ONLINE_PROVIDER_H
