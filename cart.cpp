
//
// Created by Andrea Lipperi on 14/11/22.
//

#include "cart.h"

using namespace std;

Cart::Cart(const string &client) {

    username_client = client;
    num_prod = 0;

}

Cart::~Cart() {
    remove_all();
}

void Cart::add_product(std::shared_ptr<Product> prod) {

    products.push_back(std::move(prod));
    update_num(put_in);
}

void Cart::update_num(int control) {
    if (control == put_in) {
        num_prod = num_prod + 1;
    } else if (control == cc) {
        num_prod = num_prod - 1;
    }
}

void Cart::remove_one(int index) {
    if(index < products.size()){
        auto iteretor_to_remove= products.begin()+index;
        products.erase(iteretor_to_remove);
        update_num(cc);
    }
    else
        std::cout<<"Invalid index provided."<< std::endl;
}

void Cart::remove_all() {
    for (int i = 0; i < num_prod; i++) {
        remove_one(i);
    }
}