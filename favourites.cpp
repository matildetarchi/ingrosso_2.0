//
// Created by Matilde Tarchi on 02/08/22.
//

#include "Favourites.h"
using namespace std;



Favourites::Favourites( const string &client) {

    username_client=client;
}

Favourites::~Favourites(){
    remove_all();
}


void Favourites:: update_num_prod(int control) {
    if (control==add) {
        num_prod = num_prod + 1;
    } else if (control==remove) {
        num_prod=num_prod-1;
    }
}

void Favourites::add_product( std::shared_ptr<Product> prod){
    products.push_back(std::move(prod));
    update_num_prod(add);
}

void Favourites::remove_all() {
    for (int i=0;i<num_prod; i++) {
        remove_one(i);
    }
}

//TODO fare con smart_ptr
/*void Favourites::remove_one(int index) {
    Product* p=products[index];
    delete p;
    update_num_prod(remove);
}*/
