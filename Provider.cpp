//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Provider.h"

using namespace std;

Provider::Provider():User(){}

Provider::Provider( const string &t, const string &bn,const string &a, const string &e,
                const string &password, const string &us, const string &c) : User(t, bn, a, e, password, us, c){

    order = make_shared<OrdersList>(us);
    store = make_shared<Store>(us);
}

Provider::~Provider() {

}

void Provider::accept_order(int id_order) {
    db_order->change_status("A", id_order);
}

void Provider::denied_order(int id_order) {
    db_order->change_status("D", id_order);
}

bool Provider :: delete_prod(int id_prod){
    if (!db_store->remove_from_db(id_prod)) {
        return false;
    }else
        return true;
}

bool Provider:: modify_prod(int id_store, string desc, double price, int a_q ){
    db_store->change_data(id_store, desc, price, a_q);

    vector<std::shared_ptr<Product>> prod_list;
    prod_list = store->get_products();
    int num_prod = prod_list.size();
    int i = 0;
    while ( i<= num_prod && prod_list[i]->get_id_store() != id_store){
        i++;
    }
    if(i> num_prod){
        return false;
    }else {
        prod = prod_list[i];
        prod->set_desc(desc);
        prod->set_price(price);
        prod->set_available_quantity(a_q);
        return true;
    }
}

bool Provider:: add_prod(const string& desc, double price, int quantity, int a_quantity, const string&  username_prov, const string& sub_category){

    shared_ptr<Product> new_prod = make_shared<Product> (desc, price, 0, a_quantity, username_prov, sub_category);
    store->add_to_store(new_prod);
    db_store->add_to_db();
}

void Provider::delete_objects_of_user() {
    store->remove_all();
}

