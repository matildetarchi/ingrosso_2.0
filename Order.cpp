//
// Created by Matilde Tarchi on 08/07/23.
//

#include "Order.h"


Order::Order(const string &s, const string &d, const string &u_c, int id_p){

    //TODO devo mettere anche product?
    status = s;
    date_order = d;
    username_client = u_c;
    id_s_product = id_p;

}

Order::~Order() {};