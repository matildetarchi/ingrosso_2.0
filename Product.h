//
// Created by dario on 23/06/2023.
//

#ifndef INGROSSO_ONLINE_PRODUCT_H
#define INGROSSO_ONLINE_PRODUCT_H
#include <iostream>
#include <string>

using namespace std;
class Product {

public:

    Product();
    Product(const string &desc, float price, int quantity, int q_available, const string &u_p, const string &sub);
    ~Product(){};

    const string &get_desc(){
         return description;
    }

    float &get_price(){
        return price;
    }
    [[nodiscard]] int get_q_available()const{
        return q_available;
    }
    [[nodiscard]] int get_quantity() const {
        return quantity;
    }

    string get_username_prov(){
        return username_prov;
    }

    string get_subcategory() {
        return subcategory;
    }

    [[nodiscard]] int get_id_store() const {
        return id_store;
    }

    void set_desc(const string &desc) {
        description = desc;
    }

    void set_price(float p);

    void set_quantity(int q);

    void set_available_quantity(int a_q) {
            q_available = a_q;
    }

    void set_subcategory(const string &sub) {
        subcategory = sub;
    }

    void set_username_prov(const string &u_p) {
        username_prov = u_p;
    }

    void set_id_store(int id_s) {
        id_store=id_s;
    }
private:

    string description;
    float price;
    string username_prov;
    int quantity;
    string subcategory;
    int id_store;
    int q_available;

};


#endif //INGROSSO_ONLINE_PRODUCT_H
