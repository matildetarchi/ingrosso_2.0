//
// Created by Andrea Lipperi on 14/11/22.
//

#include "Store.h"
using namespace std;



Store::Store(const string &provider) {
    username_prov = provider;
}

Store::~Store() {
    remove_all();
}

void Store::update_num(int control) {
    if (control==add) {
        num_prod=num_prod+1;
    } else {
        num_prod=num_prod-1;
    }
}

void Store::add_to_store(Product* prod) {
    store.push_back(prod);
    update_num(add);
}

void Store::remove_one(int index) {

    Product* p = store[index];
    delete p;
    update_num(cancel);

}

void Store::remove_all() {
    for( int i = 0; i<num_prod; i++)
        remove_one(i);
}


