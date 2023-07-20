//
// Created by Matilde Tarchi on 08/07/23.
//

#include "Order.h"


Order::Order(const string &s, Date* d, const string &u_c, int id_p){

    //TODO devo mettere anche product e date?
    status = s;
    username_client = u_c;
    id_s_product = id_p;

}

Order::~Order() {};