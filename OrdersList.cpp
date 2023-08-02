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


void add_order( shared_ptr<Order> ord)
{
    //TODO aggiungere nella lista
}
void OrdersList::remove_one(int index) {
    Order* o = orders[index];
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
