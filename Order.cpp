//
// Created by dario on 24/06/2023.
//

#include "Order.h"



Order::Order(Product* p, string s, string d, string u_o, int id_o){

    prod=p;
    status=s;
    date_order=d;
    username_other=u_o;
    id_s_order=id_o;

}