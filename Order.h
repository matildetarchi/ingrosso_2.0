//
// Created by Matilde Tarchi on 08/07/23.
//

#ifndef INGROSSO_ONLINE_ORDER_H
#define INGROSSO_ONLINE_ORDER_H

#include "OrderProduct.h"

class Order {
public:

    Order(const string &s, const string &d, const string &u_c, int id_s_p);

    ~Order();

    int get_id_s_prod() {
        return id_s_product;
    }

    void set_id_s_prod(int id_s_p) {
        this->id_s_product = id_s_p;
    }

    int get_num_prod() const{
        return num_prod;
    }

    const string &get_status(){
        return status;
    }

    void set_status(int id_s_p, const string &new_status){
        if( get_id_s_prod()==id_s_p)
            status = new_status;
    }

    Product* get_prod() {
        return prod;
    }

    //TODO è da fare qui set prod?

    const string &get_date() {
        return date_order;
    }

    void set_date(string date_o) {
        this->date_order=date_o;
    }

    const string &get_us_client() {
        return username_client;
    }

    //TODO implementare funzione
    double get_total(Order* o);

    vector<OrderProduct*> order_p;

private:

    Product* prod;
    int num_prod;
    int id_s_product;
    string status;
    string date_order;
    string username_client;

};


#endif //INGROSSO_ONLINE_ORDER_H
