//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_PROVIDER_H
#define INGROSSO_ONLINE_PROVIDER_H

#include "User.h"


using namespace std;


class Provider: virtual public User {
public:

    Provider(const string &us);
    Provider(const string &t, const string &bn, const string &a, const string &e, const string &password, const string &us, const string &c);
    ~Provider() override;


    shared_ptr<Store> get_store() override {
        return store;
    }

    void set_store(shared_ptr<Store> s) {
        store = s;
    }

    shared_ptr<Cart> get_cart() override{}

    shared_ptr<Favourites> get_fav() override{}

    void add_to_cart(shared_ptr<Product> p) override {};
    void add_to_fav(shared_ptr<Product> p) override {};
    bool remove_from_cart(int id_prod) override {};
    bool remove_from_fav(int id_prod) override {};

    void delete_objects_of_user() override;
    bool modify_prod (int id_store, string desc, double price, int a_q ) override;
    void add_prod(const string& desc, double price, int quantity, int a_quantity, const string&  username_prov, const string& sub_category) override;

private:
    shared_ptr<Store> store;
    shared_ptr<Product> prod;
};


#endif //INGROSSO_ONLINE_PROVIDER_H
