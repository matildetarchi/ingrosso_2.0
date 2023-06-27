//
// Created by dario on 24/06/2023.
//

#ifndef INGROSSO_ONLINE_ORDER_H
#define INGROSSO_ONLINE_ORDER_H
#include "Product.h"

using namespace std;

class Order {

public:

    Order(Product* p, string s, string d, string u_o, int id_s_o);
    ~Order(){};

    const string get_status(){
        return status;
    }
    Product* get_prod(){
        return prod;
    }
    void set_prod(Product* p){
        prod=p;
    }

    const int get_id_s_ord(){
        return id_s_order;
    }
    void set_id_s_ord(int id_s_order){
        this->id_s_order=id_s_order;
    }

    const string get_date(){
        return date_order;
    }
    void set_date(string date_order){
        this->date_order=date_order;
    }

    const string get_us_other(){
        return username_other;
    }

    void set_status(int id_s_order, const string &new_status){
        if( get_id_s_ord()==id_s_order)
            status=new_status;
    }

private:

    Product* prod;
    std::string status;
    string date_order;
    std::string username_other;
    int id_s_order;

};


#endif //INGROSSO_ONLINE_ORDER_H
