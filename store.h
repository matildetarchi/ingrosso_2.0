//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_STORE_H
#define INGROSSO_ONLINE_STORE_H

#define put_in 0
#define cc 1
#include <vector>
#include "Product.h"
#include <memory>

using namespace std;
class Store{
public:

    Store();
    explicit Store(const string &provider);

    ~Store();

    vector <std::shared_ptr<Product>> get_products() {
        return store;
    }

    [[nodiscard]] int get_id() {
        return id;
    }

    [[nodiscard]] int get_num_prod() const {
        return num_prod;
    }

    const string &get_prov() {
        return username_prov;
    }

    void add_to_store(const shared_ptr<Product>& product);
    void update_num(int control);
    void remove_one(int index);
    void remove_all();


private:
    int id;
    string username_prov;
    int num_prod;
    vector<std::shared_ptr<Product>> store;


};

#endif // INGROSSO_ONLINE_STORE_H