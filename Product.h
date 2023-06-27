//
// Created by dario on 23/06/2023.
//

#ifndef INGROSSO_ONLINE_PRODUCT_H
#define INGROSSO_ONLINE_PRODUCT_H
#include <iostream>
#include <string>


class Product {

public:

    Product(std::string desc, double price, int quant, const std::string u_p, const std::string sub);
    ~Product(){};

    const std::string get_desc(){
         return desc;
    }

    void set_desc(const std::string &desc) {
        this->desc = desc;
    }

    double get_price(){
        return price;
    }

    void set_price(double price) {
        this->price = price;
    }
    int get_quantity(){
        return quantity;
    }

    void set_quantity(int quantity) {
        this->quantity = quantity;
    }

    std::string get_username_prov(){
        return username_prov;
    }

    std::string get_subcategory() {
        return sub;
    }

    void set_subcategory(std::string sub) {
        this->sub = sub;
    }

    void set_username_prov(std::string u_p) {
        this->username_prov = u_p;
    }

private:
    std::string desc;
    double price;
    std::string username_prov;
    int quantity;
    std::string sub;

};


#endif //INGROSSO_ONLINE_PRODUCT_H