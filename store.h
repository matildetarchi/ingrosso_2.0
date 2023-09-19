//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_STORE_H
#define INGROSSO_ONLINE_STORE_H

#define add 0
#define cancel 1
#include <vector>
#include "Product.h"

using namespace std;
class Store{
public:

    explicit Store(const string &provider);

    ~Store();


    int get_num_prod() const {
        return num_prod;
    }

    const string &get_prov() {
        return username_prov;
    }

    void add_to_store(Product* product);
    void update_num(int control);
    void remove_one(int index);
    void remove_all();

    vector<Product*> store;

private:
    string username_prov;
    int num_prod;
    Product* prod;

};

#endif // INGROSSO_ONLINE_STORE_H