//
// Created by dario on 23/06/2023.
//

#include "Product.h"

using namespace std;

Product::Product(){};

Product::Product( const string &d, double p, int q, int q_a, const string &u_p, const string &s) {

    description = d;
    price = p;
    quantity = q;
    username_prov = u_p;
    subcategory = s;
    q_available=q_a;

}

