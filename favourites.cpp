///
// Created by Matilde Tarchi on 02/08/22.
//

#include "favourites.h"
using namespace std;



Favourites::Favourites( const string &client) {

    username_client=client;
    num_prod = 0;
}

Favourites::~Favourites(){
    remove_all();
}

void Favourites::add_product( std::shared_ptr<Product> prod){
    products.push_back(std::move(prod));
    update_num_prod(put_in);
}

void Favourites:: update_num_prod(int control) {
    if (control==put_in) {
        num_prod = num_prod + 1;
    } else if (control==cc) {
        num_prod=num_prod-1;
    }
}

void Favourites::remove_one(int index) {
    if(index<products.size()){
        auto iteretor_to_remove = products.begin()+index;
        products.erase(iteretor_to_remove);
        update_num_prod(cc);
    }
    else
        std::cout<<"Invalid index provided."<< std::endl;
}

void Favourites::remove_all() {
    for (int i=0;i<num_prod; i++) {
        remove_one(i);
    }
}