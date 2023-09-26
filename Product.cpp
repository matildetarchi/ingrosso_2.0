//
// Created by dario on 23/06/2023.
//

#include "Product.h"

using namespace std;

Product::Product()= default;

Product::Product( const string &d, float p, int q, int q_a, const string &u_p, const string &s) {

    description = d;
    price = p;
    quantity = q;
    username_prov = u_p;
    subcategory = s;
    q_available=q_a;

}

void Product::set_price(float p){
    if (p > 0) {
        price = p;
    } else {
        std::cout << "Valore non valido." << std::endl;
    }
}

void Product::set_quantity(int q) {
    if (q > 0) {
        quantity = q;
    } else {
        std::cout << "Valore non valido." << std::endl;
    }
}

