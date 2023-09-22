//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Provider.h"

using namespace std;

Provider::Provider( const string &us):User( us){
    store = make_shared<Store>(us);
}

Provider::Provider( const string &t, const string &bn,const string &a, const string &e,
                const string &password, const string &us, const string &c) : User(t, bn, a, e, password, us, c){

    store = make_shared<Store>(us);

}

Provider::~Provider() {

}



bool Provider:: modify_prod(int id_store, string desc, double price, int a_q ){

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
}

void Provider::delete_objects_of_user() {
    store->remove_all();
}

