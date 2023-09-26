//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Client.h"


using namespace std;

Client::Client(const string &us) : User(us){
    cart = make_shared<Cart>(us);
    fav = make_shared<Favourites>(us);
}

Client::Client( const string &t, const string &bn,const string &a, const string &e,
               const string &password, const string &us, const string &c) : User(t, bn, a, e, password, us, c){

    cart = make_shared<Cart>(us);
    fav = make_shared<Favourites>(us);
}

Client::~Client() = default;


void Client::add_to_cart(shared_ptr<Product> p) {
    cart->add_product(p);
}

void Client::add_to_fav(shared_ptr<Product> p) {
    fav->add_product(p);
}

bool Client::remove_from_cart(int id_prod){

    vector<std::shared_ptr<Product>> prod_l;
    prod_l = cart->get_products();
    int num_prod = prod_l.size();
    int i = 0;
    while ( i<= num_prod && prod_l[i]->get_id_store() != id_prod){
        i++;
    }
    if(i>num_prod)
        return false;
    else {
        cart->remove_one(i);
        return true;
    }
}

bool Client::remove_from_fav(int id_prod){

    vector<std::shared_ptr<Product>> prod_list;
    prod_list = fav->get_products();
    int num_prod = prod_list.size();
    int i = 0;
    while ( i<= num_prod && prod_list[i]->get_id_store() != id_prod){
        i++;
    }
    if(i>num_prod)
        return false;
    else {
        fav->remove_one(i);
        return true;
    }
}

void Client::delete_objects_of_user() {
    cart->remove_all();
    fav->remove_all();
}


