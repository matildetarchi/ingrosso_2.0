//
// Created by Matilde Tarchi on 02/08/22.
//

#include "favourites.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Favourites::Favourites() {}

Favourites::Favourites(const string &desc_product, double price, const string &client, const string &provider) {

    desc_prod[num_prod]=desc_product;
    price_prod[num_prod]=price;
    username_cust=client;
    username_prov[num_prod]=provider;
    update_num_prod(add);

}

void Favourites::remove_one(int index) {
    desc_prod.erase(desc_prod.begin()+index);
    price_prod.erase(price_prod.begin()+index);
    username_prov.erase(username_prov.begin()+index);
    update_num_prod(remove);
}
