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

    Product(const string &desc, double price, int quant, const string &u_p, const string &sub, int id_st);
    ~Product(){};

    const string &get_desc(){
         return description;
    }

    void set_desc(const string &desc) {
        this->description = desc;
    }

    double &get_price(){
        return price;
    }

    void set_price(double p){
        this->price = p;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int q) {
        this->quantity = q;
    }

    string get_username_prov(){
        return username_prov;
    }

    string get_subcategory() {
        return subcategory;
    }

    void set_subcategory(const string &sub) {
        this->subcategory = sub;
    }

    void set_username_prov(const string &u_p) {
        this->username_prov = u_p;
    }

    /*int &get_id_db() {
        return id_db_prod;
    }

    int get_id_store() const {
        return id_store;
    }*/

private:
    //int id_db_prod; //Variabile per memorizzare l'id che il prodotto ha nel database
    string description;
    double price;
    string username_prov;
    int quantity;
    string subcategory;
    int id_store;

};


#endif //INGROSSO_ONLINE_PRODUCT_H
