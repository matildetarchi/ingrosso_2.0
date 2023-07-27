//
// Created by Andrea Lipperi on 16/11/22.
//


#include "OrdersList.h"

using namespace std;

OrdersList::OrdersList(const string &user): username_user(user){
}

OrdersList::~OrdersList(){
    remove_all();
}

void OrdersList::add_order( const string &status, Date *date_order, const string &username_other, int id_s_order){

    std::shared_ptr<Order> o = std::make_shared<Order>(status,username_other, id_s_order);
    o->set_date(date_order);
    orders.push_back(std::move(o));
    update_num(add);
}

void OrdersList::remove_one(int index) {
    Order* o=orders[index];
    delete o;
    update_num(cancel);
}

void OrdersList::remove_all() {
    for (int i=0;i<num_order; i++) {
        remove_one(i);
    }
}
void OrdersList::update_num(int control) {
    if (control==add) {
        num_order=num_order+1;
    } else {
        num_order=num_order-1;
    }
}
