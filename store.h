//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_STORE_H
#define INGROSSO_ONLINE_STORE_H

#define add 0
#define cancel 1
#include <string>
#include <vector>

using namespace std;
class Store{
public:
    Store();
    Store(int quant,const string &sub, double price,const string &desc, const string &provider);

    virtual ~Store() {}
    int get_quantity(int index) {
        return available_quantity[index];
    }

    const string get_prod(int index) {
        return subcategory[index];
    }

    double get_price(int index) {
        return price_product[index];
    }
    int get_num_prod() {
        return num_prod;
    }

    const string get_desc(int index) {
        return description_prod[index];
    }
    const string get_prov() {
        return username_prov;
    }
    void set_desc_prod(int index, const string &new_desc){
        Store::description_prod[index]=new_desc;
    }
    void set_price(int index, double &new_price){
        Store::price_product[index]=new_price;
    }
    void set_quantity(int index, int &new_quantity){
        Store::available_quantity[index]=new_quantity;
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

    std::vector<int> available_quantity;
    std::vector<string> subcategory;
    std::vector<double> price_product;
    std::vector<string> description_prod;
    string username_prov;
    int num_prod;

};

#endif // INGROSSO_ONLINE_STORE_H