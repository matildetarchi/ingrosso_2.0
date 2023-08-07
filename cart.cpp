
//
// Created by Andrea Lipperi on 14/11/22.
//


#include "cart.h"

using namespace std;

Cart::Cart(const string &client) {

    username_client = client;

}

Cart::~Cart() {
    remove_all();
}

void Cart::update_num(int control) {
    if (control == add) {
        num_prod = num_prod + 1;
    } else if (control == cancel) {
        num_prod = num_prod - 1;
    }
}


//prende da Cart.h con C grande
void Cart::add_product(std::shared_ptr<Product> prod) {

    products.push_back(std::move(prod));
    update_num(add);
}


void Cart::remove_all() {
    for (int i = 0; i < num_prod; i++) {
        remove_one(i);
    }
}


//TODO fare con smart_ptr
/*void Cart::remove_one(int index) {

    Product p = products[index];
    delete p;
    update_num(cancel);
}*/