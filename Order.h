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

    Order(int id, string s, string u_client);

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

    vector<shared_ptr<Product>> get_order_prod() {
        return order_p;
    }

    shared_ptr<Date> get_date() {
        return date;
    }
    const string &get_us_client() {
        return username_client;
    }

    void set_status(const string &new_status){
            status = new_status;
    }

    void set_date(shared_ptr<Date> d) {
        date = std::move(d);
    }


    double get_total(const shared_ptr<Order>& o);


    void add_to_order(shared_ptr<Product> p);

    void update_num(int control);

    void remove_one(int index);
    void remove_all();



private:

    shared_ptr<Date> date;
    int num_prod;
    int id;
    string status;
    string username_client;
    vector<shared_ptr<Product>> order_p;
};


#endif //INGROSSO_ONLINE_ORDER_H
