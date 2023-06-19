//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_ORDERS_H
#define INGROSSO_ONLINE_ORDERS_H

#define add 0
#define cancel 1
#include "store.h"
#include <string>
#include <vector>
#include "database.h"
#include <SQLiteCpp/Statement.h>
#include <iostream>


using namespace std;

class Orders{
public:
    Orders();
    Orders(int quant, const string &desc,double price_prod, const string &st, const string &d, const string &user, const string &other, int id_ord);

    virtual ~Orders() {}
    int get_quantity(int index) {
        return quantity[index];
    }

    int get_id_ord(int index){
        return id_order[index];
    }
    const string get_status(int index){
        return status[index];
    }
    const string get_date(int index){
        return date_order[index];
    }

    const string get_us_other(int index){
        return username_other[index];
    }
    int get_num_prod(){
        return num_prod;
    }
     double get_price(int index){
        return price[index];
    }
    string get_desc_prod(int index){
        return desc_prod[index];
    }
    const string get_username_user(){
        return username_user;
    }
    void set_status(const string &cod_order, const string &new_status){
        for (int i=0;i<get_num_prod(); i++){
            if( get_id_ord(i)==stoi(cod_order))
                status[i]=new_status;
        }
    }

    void update_num(int control) {
        if (control==add) {
            num_prod=num_prod+1;
        } else {
            num_prod=num_prod-1;
        }
    }
    void remove_one(int index);

private:
    std::vector<int> quantity;
    std::vector<double> price;
    std::vector<string> desc_prod;
    std::vector<string> status;
    std::vector<string> date_order;
    string username_user;
    std::vector<string> username_other;
    std::vector<int> id_order;
    int num_prod;
};

#endif // INGROSSO_ONLINE_ORDERS_H