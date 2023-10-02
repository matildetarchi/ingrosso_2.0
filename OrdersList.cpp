//
// Created by Andrea Lipperi on 16/11/22.
//


#include "OrdersList.h"

#include <utility>

using namespace std;

OrdersList::OrdersList() = default;

OrdersList::OrdersList(string user): username_user(std::move(user)), num_order(0){
}

OrdersList::~OrdersList(){
    remove_all();
}


void OrdersList::add_order( const shared_ptr<Order>& ord) {
   orders.push_back(ord);
   update_num(put_in);
}

void OrdersList::update_num(int control) {
    if (control==put_in) {
        num_order = num_order+1;
    } else {
        num_order = num_order-1;
    }
}

void OrdersList::remove_one(int index) {
    if(index<orders.size()){
        auto iteretor_to_remove=orders.begin()+index;
        orders.erase(iteretor_to_remove);
        update_num(cc);
    }
    else
        std::cout<<"Invalid index provided."<< std::endl;
}

void OrdersList::remove_all() {
    for (int i=0;i<num_order; i++) {
        remove_one(i);
    }
}

bool OrdersList::modify_status(int id_order, const string &new_status){

    bool result;
    for (const shared_ptr<Order>& order : orders) {
        if (order->get_id() == id_order) {
            order->set_status(new_status);
            result = true;
            break;
        }
        else
            result = false;
    }
    return result;
}
