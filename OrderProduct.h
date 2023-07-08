//
// Created by dario on 24/06/2023.
//

#ifndef INGROSSO_ONLINE_ORDERPRODUCT_H
#define INGROSSO_ONLINE_ORDERPRODUCT_H
#include "Product.h"

using namespace std;
//TODO puo essere che questa sia derivata da order o viceversa?
class OrderProduct {

public:
    //TODO riguardare come sono gestiti gli ordini in provider e client
    OrderProduct(const string &u_p, int id_st);
    ~OrderProduct();


    Product* get_prod() {
        return prod;
    }

    void set_prod(Product* p) {
        prod = p;
    }

    int get_id_store() const {
        return id_store;
    }

    const string &get_us_provider() {
        return username_provider;
    }


private:

    Product* prod;
    string username_provider;
    int id_store;

};


#endif //INGROSSO_ONLINE_ORDERPRODUCT_H
