//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_STORE_H
#define INGROSSO_ONLINE_STORE_H

#define add 0
#define cancel 1
#include <string>
#include <vector>
#include "Product.h"
#include <memory>

using namespace std;
class Store{
public:

    explicit Store(const string &provider);

    ~Store();

    vector <std::shared_ptr<Product>> get_products() {
        return store;
    }


    int get_num_prod() const {
        return num_prod;
    }

    const string &get_prov() {
        return username_prov;
    }

    void add_to_store(shared_ptr<Product> product);
    void update_num(int control);
    void remove_one(int index);
    void remove_all();


private:
    string username_prov;
    int num_prod;
    vector<std::shared_ptr<Product>> store;


};

#endif // INGROSSO_ONLINE_STORE_H