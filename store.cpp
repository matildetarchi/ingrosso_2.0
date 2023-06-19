//
// Created by Andrea Lipperi on 14/11/22.
//

#include "store.h"

using namespace std;

Store::Store() {}

Store::Store(int quant, const string &sub, double price, const string &desc, const string &provider){
    available_quantity.push_back(quant);
    subcategory.push_back(sub);
    price_product.push_back(price);
    description_prod.push_back(desc);
    username_prov = provider;
    update_num(add);
}

void Store::remove_one(int index) {

    available_quantity.erase(available_quantity.begin()+index);
    subcategory.erase(subcategory.begin()+index);
    price_product.erase(price_product.begin()+index);
    description_prod.erase(description_prod.begin()+index);
    username_prov.erase(username_prov.begin()+index);
    update_num(cancel);

}


