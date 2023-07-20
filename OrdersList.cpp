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

    Order* o = new Order(status,username_other, id_s_order);
    o->set_date(date_order);
    orders.push_back(o);
    update_num(add);
}

void OrdersList::remove_one(int index) {
    Order* o=orders[index];
    delete o;
    update_num(cancel);
}

void OrdersList::remove_all() {
    for (int i=0;i<num_prod; i++) {
        remove_one(i);
    }
}
void OrdersList::update_num(int control) {
    if (control==add) {
        num_prod=num_prod+1;
    } else {
        num_prod=num_prod-1;
    }
}
