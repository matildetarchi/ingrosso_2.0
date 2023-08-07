//
// Created by Matilde Tarchi on 08/07/23.
//

#include "Order.h"

#include <utility>
#define add 1
#define cancel 0

Order::Order(string s, string u_c): status(std::move(s)), username_client(std::move(u_c)),  date(nullptr){
}

Order::~Order() {
    remove_all();
}

void add_order( shared_ptr<Order> ord)
{
    //TODO aggiungere nella lista
}

double Order::get_total(unique_ptr<Order> o) {
    int s = 0;
    for(int i = 0; i<o->num_prod; i++) {
        shared_ptr<Product> p = o->get_prod(i);
        s += p->get_price();
    }
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