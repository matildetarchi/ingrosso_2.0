//
// Created by Andrea Lipperi on 14/11/22.
//


#include "Store.h"
using namespace std;


Store::Store()= default;

Store::Store(const string &provider) {
    username_prov = provider;
    num_prod = 0;
}

Store::~Store() {
    remove_all();
}


void Store::add_to_store(const shared_ptr<Product>& prod) {
    if ( prod != nullptr) {
        store.push_back(prod);
        update_num(0);
    }
}

void Store::update_num(int control) {
    if (control==put_in) {
        num_prod = num_prod+1;
    } else {
        num_prod = num_prod-1;
    }
}

void Store::remove_one(int index) {

    if(index<store.size()){
        auto iteretor_to_remove= store.begin()+index;
        store.erase(iteretor_to_remove);
        update_num(cc);
    }
    else
        std::cout<<"Invalid index provided."<< std::endl;
}



void Store::remove_all() {
    for( int i = 0; i<num_prod; i++)
        remove_one(i);
}