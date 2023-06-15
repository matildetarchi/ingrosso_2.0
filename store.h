//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_STORE_H
#define INGROSSO_ONLINE_STORE_H

#include <string>
using namespace std;
class Store{
public:
    Store();
    Store(int quant,const string &sub, double price,const string &desc, const string &provider);

    int get_quantity() {
        return available_quantity;
    }

    const string get_prod() {
        return subcategory;
    }

    double get_price() {
        return price_product;
    }

    string get_desc() {
        return description_prod;
    }
    const string get_prov() {
        return username_prov;
    }

    //methods

    void add();
    bool remove(int id_store);
    void changeData(int id_store);
    vector<string> select_to_modify(int id_store);
    vector<vector<string>> select_for_client(const string &sub_name, const string &disp, const string &order="store.id");
    vector<vector<string>> select_for_prov(const string &username, const string &order="store.id");
    int select_count_for_client(const string &sub_name, const string &disp);
    int select_count_for_prov(const string &username);

private:

    int available_quantity;
    string subcategory;
    double price_product;
    string description_prod;
    string username_prov;

};

#endif // INGROSSO_ONLINE_STORE_H