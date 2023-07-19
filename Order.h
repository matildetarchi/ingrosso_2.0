//
// Created by Matilde Tarchi on 08/07/23.
//

#ifndef INGROSSO_ONLINE_ORDER_H
#define INGROSSO_ONLINE_ORDER_H

#include "Product.h"
#include "Date.h"
#include <memory>
#include <vector>



using namespace std;
class Order {
public:

    Order(string s, string u_client, int id_s_p);

    ~Order();

    int get_id_s_prod() const {
        return id_s_product;
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

    void set_product(Product* p){
        prod=p;
    }


    Date* get_date() {
        return date;
    }

    void set_date(Date *d) {
        date = d;
    }

    const string &get_us_client() {
        return username_client;
    }

    //TODO implementare funzione
    double get_total(Order* o);

    void add_order(unique_ptr<Product*> p){
        order_p.push_back(std::move(p));
    };

    void update_num(int control);
    void remove_one(int index);
    void remove_all();



private:

    Date* date;
    Product* prod;
    int num_prod;
    int id_s_product;
    string status;
    string username_client;
    vector<unique_ptr<Product*>> order_p;
};


#endif //INGROSSO_ONLINE_ORDER_H
