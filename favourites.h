//
// Created by Matilde Tarchi on 29/07/22.
//

#ifndef INGROSSO_ONLINE_FAVOURITES_H
#define INGROSSO_ONLINE_FAVOURITES_H

#include <string>
#include <vector>
#include "Product.h"
#include <memory>
#define add 0
#define remove 1
using namespace std;

class Favourites{
public:

    explicit Favourites(const string &client);

    ~Favourites();

    const string &get_client(){
        return username_client;
    }

    int get_num_prod() const{
        return num_prod;
    }

    vector <std::shared_ptr<Product>> get_products() {
        return products;
    }

    void add_product( std::shared_ptr<Product> prod);

    void update_num_prod(int control);

    void remove_all();
    void remove_one(int index);



private :

    string username_client;
    int num_prod;
    vector<std::shared_ptr<Product>> products;

};

#endif //INGROSSO_ONLINE_FAVOURITES_H
