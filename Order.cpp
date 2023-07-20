//
// Created by Matilde Tarchi on 08/07/23.
//

#include "Order.h"

#include <utility>
#define add 1
#define cancel 0

Order::Order(string s, string u_c, int id_p): status(std::move(s)), username_client(std::move(u_c)), id_s_product(id_p), date(nullptr), prod(nullptr){
}

Order::~Order() {
    remove_all();
}

double Order::get_total(Order *o) {
    return 0;
};



/*void Order::remove_one(int index) {
    Product* o=order_p[index];
    delete o;
    update_num(cancel);
}*/

void Order::remove_all() {
    for (int i=0;i<num_prod; i++) {
        remove_one(i);
    }
}

void Order::update_num(int control) {
    if (control==add) {
        num_prod=num_prod+1;
    } else {
        num_prod=num_prod-1;
    }
}