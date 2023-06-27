//
// Created by Matilde Tarchi on 29/07/22.
//

#ifndef INGROSSO_ONLINE_FAVOURITES_H
#define INGROSSO_ONLINE_FAVOURITES_H

#include <string>
#include <vector>
#include "Product.h"
#define add 0
#define remove 1
using namespace std;

class Favourites{
public:
    Favourites();
    Favourites(const string client);

    ~Favourites();

    const string get_client(){
        return username_client;
    }

    const int get_num_prod() const{
        return num_prod;
    }

    void add_product(const string desc, double price, const string username_prov);
    void update_num_prod(int control);
    void remove_all();
    void remove_one(int index);


    vector<Product*> products;

private :

    string username_client;
    int num_prod;

};

#endif //INGROSSO_ONLINE_FAVOURITES_H
