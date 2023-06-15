
//
// Created by Andrea Lipperi on 14/11/22.
//


#include "cart.h"
#include <iostream>
#include <string>

using namespace std;

Cart::Cart(){}

Cart::Cart(int quant, const string &desc_product, double price, const string &client, const string &provider) {

    desc_prod.push_back(desc_product);
    price_prod.push_back(price);
    quantity.push_back(quant);
    username_client.push_back(client);
    username_prov.push_back(provider);
    update_num(add);

}

void Cart::remove_all(const std::string usernam_c) {
    for (int i=0;i<num_prod; i++) {
        if (username_client[i]==usernam_c) {
            remove_one(i);
        }
    }
}
void Cart::remove_one(int index) {
    username_client.erase(username_client.begin()+index);
    quantity.erase(quantity.begin()+index);
    desc_prod.erase(desc_prod.begin()+index);
    price_prod.erase(price_prod.begin()+index);
    username_prov.erase(username_prov.begin()+index);
}