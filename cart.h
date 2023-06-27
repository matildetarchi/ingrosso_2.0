//
// Created by Matilde Tarchi on 29/07/22.
//


#ifndef INGROSSO_ONLINE_CART_H
#define INGROSSO_ONLINE_CART_H

#include <string>
#include "store.h"
#include "Product.h"
#include <vector>


using namespace std;

class Cart {
public:
    Cart();
    Cart(const string client);
    ~Cart();


    const string get_client(){
        return username_client;
    }

    const int get_num_prod() const{
        return num_prod;
    }
    void add_product(const string desc, double price, int quantity, const string username_prov);

    void update_num(int control);

    void remove_all();
    void remove_one(int index);

    std::vector<Product*> products;

private:
    string username_client;
    int num_prod;
};

#endif //INGR_ONLINE_CART_H
