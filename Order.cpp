//
// Created by Matilde Tarchi on 08/07/23.
//

#include "Order.h"

#include <utility>
#define put_in 1
#define cancel 0

Order::Order(string s, string u_c): status(std::move(s)), username_client(std::move(u_c)),  date(nullptr){
}

Order::~Order() {
    remove_all();
}


void Order::add_to_order(shared_ptr<Product> p){
    order_p.push_back(std::move(p));
    update_num(put_in);
}

void Order::update_num(int control) {
    if (control==put_in) {
        num_prod=num_prod+1;
    } else {
        num_prod=num_prod-1;
    }
}

double Order::get_total(unique_ptr<Order> o) {
    int s = 0;
    vector<shared_ptr<Product>> products = o->get_order_prod();
    for(int i = 0; i<o->num_prod; i++) {
        shared_ptr<Product> p = products[i];
        int price = p->get_price();
        s += price *(p->get_quantity());
    }
    return s;
}

void Order::remove_one(int index) {
    if(index<order_p.size()){
        auto iteretor_to_remove=order_p.begin()+index;
        order_p.erase(iteretor_to_remove);
        update_num(cancel);
    }
    else
        std::cout<<"Invalid index provided."<< std::endl;
}

void Order::remove_all() {
    for (int i=0;i<num_prod; i++) {
        remove_one(i);
    }
}
