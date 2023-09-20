//
// Created by Matilde Tarchi on 29/07/22.
//

#ifndef INGROSSO_ONLINE_CART_H
#define INGROSSO_ONLINE_CART_H


#include "store.h"

#define put_in 0
#define cc 1


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

    void update_num(int control);

    void remove_one(int index);
    void remove_all();



private:
    string username_client;
    int num_prod;

    vector<std::shared_ptr<Product>> products;

};

#endif //INGROSSO_ONLINE_CART_H