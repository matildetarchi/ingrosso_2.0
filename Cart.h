//
// Created by Matilde Tarchi on 29/07/22.
//


#ifndef INGROSSO_ONLINE_CART_H
#define INGROSSO_ONLINE_CART_H

#include <string>
#include "Store.h"
#include "Product.h"
#include <vector>
#define add 0
#define cancel 1


using namespace std;

class Cart {
public:

    explicit Cart(const string &client);
    ~Cart();


    const string &get_client() {
        return username_client;
    }

    int get_num_prod() const{
        return num_prod;
    }

    //TODO
    int get_total();

    void add_product(Product* prod);

    void update_num(int control);

    void remove_all();
    void remove_one(int index);

    vector<Product*> products;

private:
    string username_client;
    int num_prod;
};

#endif //INGROSSO_ONLINE_CART_H
