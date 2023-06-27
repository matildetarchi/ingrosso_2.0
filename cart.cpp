
//
// Created by Andrea Lipperi on 14/11/22.
//


#include "cart.h"
#define add 0
#define cancel 1

using namespace std;

Cart::Cart(){}

Cart::Cart(const string client) {

    username_client=client;

}
Cart::~Cart() {
    remove_all();
}

void Cart::update_num(int control){
    if (control==add) {
        num_prod=num_prod+1;
    } else if (control==cancel) {
        num_prod=num_prod-1;
    }
}
void Cart::add_product(Product* prod){
    products.push_back(prod);
    update_num(add);
}


void Cart::remove_all() {
    for (int i=0;i<num_prod; i++) {
        remove_one(i);
    }
}
void Cart::remove_one(int index) {
   Product* p=products[index];
   delete p;
    update_num(cancel);
}