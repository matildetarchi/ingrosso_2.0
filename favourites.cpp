//
// Created by Matilde Tarchi on 02/08/22.
//

#include "favourites.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Favourites::Favourites() {}

Favourites::Favourites( const string client) {

    username_client=client;
}

Favourites::~Favourites(){
    remove_all();
}


void Favourites:: update_num_prod(int control) {
    if (control==add) {
        num_prod = num_prod + 1;
    } else if (control==remove) {
        num_prod=num_prod-1;
    }
}

void Favourites::add_product(const string desc, double price, const string username_prov){
    Product* p=new Product(desc,price, 1, username_prov);
    products.push_back(p);
    update_num_prod(add);
}

void Favourites::remove_all() {
    for (int i=0;i<num_prod; i++) {
        remove_one(i);
    }
}

void Favourites::remove_one(int index) {
    Product* p=products[index];
    delete p;
    update_num_prod(remove);
}
