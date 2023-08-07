//
// Created by Matilde Tarchi on 29/07/22.
//


#ifndef INGROSSO_ONLINE_CART_H
#define INGROSSO_ONLINE_CART_H

#include <string>
#include "store.h"
#include "product.h"
#include <vector>
#include <memory>
#define add 0
#define cancel 1


using namespace std;

class Cart {
public:

   explicit Cart(const string &client);
    ~Cart();


    const string &get_client(){
        return username_client;
    }

    int get_num_prod() const{
        return num_prod;
    }


    vector <std::shared_ptr<Product>> get_products() {
        return products;
    }

    void add_product(shared_ptr<Product> prod);


    void add_product(unique_ptr<Product> prod);

    void update_num(int control);

    void remove_all();
    void remove_one(int index);



private:
    string username_client;
    int num_prod;

    vector<std::shared_ptr<Product>> products;

};

#endif //INGROSSO_ONLINE_CART_H
