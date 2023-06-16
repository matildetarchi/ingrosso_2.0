//
// Created by Matilde Tarchi on 29/07/22.
//


#ifndef INGROSSO_ONLINE_CART_H
#define INGROSSO_ONLINE_CART_H
#define add 0
#define remove 1
#include <string>
#include "store.h"
using namespace std;
class Cart {
public:
    Cart();
    Cart(int quant, const string &desc_product, double price, const string &client, const string &provider);

    int get_quantity(int index) {
        return quantity[index];
    }
    const string get_prod(int index){
        return desc_prod[index];
    }
    double get_price(int index){
        return price_prod[index];
    }
    const string get_user(){
        return username_client;
    }
    const string get_prov(int index) {
        return username_prov[index];
    }

    int get_num_prod(){
        return num_prod;
    }

    void update_num(int control) {
        if (control==add) {
            num_prod=num_prod+1;
        } else if (control==remove) {
            num_prod=num_prod-1;
        }
    }

    void remove_all();
    void remove_one(int index);

private:

    std::vector<int> quantity;
    std::vector<string> desc_prod;
    std::vector<double> price_prod;
    string username_client;
    std::vector<string> username_prov;
    int num_prod;
};

#endif //INGR_ONLINE_CART_H
