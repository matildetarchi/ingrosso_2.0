//
// Created by Andrea Lipperi on 16/11/22.
//

#define only_pending 0
#include "orders.h"
#include "database.h"
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <string>
using namespace std;

Orders::Orders() {

}

Orders::Orders(int quant, const string &desc,double price_prod, const string &st, const string &d, const string &user, const string &other, int id_ord){

    quantity.push_back(quant);
    price.push_back(price_prod);
    desc_prod.push_back(desc);
    username_other.push_back(other);
    username_user=user;
    status.push_back(st);
    date_order.push_back(d);
    id_order.push_back(id_ord);
    update_num(add);
}

void Orders::remove_one(int index) {
    for(int i=0;i<num_prod;i++){

        if(id_order[i]=index){
            status.erase(status.begin()+i);
            quantity.erase(quantity.begin()+i);
            desc_prod.erase(desc_prod.begin()+i);
            price.erase(price.begin()+i);
            username_other.erase(username_other.begin()+i);
            date_order.erase(date_order.begin()+i);
            id_order.erase(id_order.begin()+i);
            update_num(cancel);

        }

    }
}
