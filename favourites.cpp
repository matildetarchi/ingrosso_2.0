//
// Created by Matilde Tarchi on 02/08/22.
//

#include "favourites.h"
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

void Favourites::remove_one(int index) {
   if(index<products.size()){
        auto iteretor_to_remove = products.begin()+index;
        products.erase(iteretor_to_remove);
        update_num_prod(remove);
    }
    else
        std::cout<<"Invalid index provided."<< std::endl;
}
