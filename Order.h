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

    Order(string s, string u_client);

    ~Order();


    int get_id() const {
        return id;
    }

    int get_num_prod() const{
        return num_prod;
    }

    const string &get_status(){
        return status;
    }

    void set_status(int id_order, const string &new_status){
        if( get_id()==id_order)
            status = new_status;
    }

    vector<unique_ptr<Product>> get_prod() {
        return order_p;
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

    //nel carrello
    void add_to_order(unique_ptr<Product> p){
        order_p.push_back(std::move(p));
    };

    void update_num(int control);


    void add_order( shared_ptr<Order> ord);
    void remove_all();

    void remove_one(int index);
    void remove_all();



private:

    Date* date;
    int num_prod;
    int id;
    string status;
    string username_client;
    vector<unique_ptr<Product>> order_p;
};


#endif //INGROSSO_ONLINE_ORDER_H
