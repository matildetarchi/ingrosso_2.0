//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_ORDERPRODUCT_H
#define INGROSSO_ONLINE_ORDERPRODUCT_H

#include "store.h"
#include <string>

using namespace std;

class OrderProduct{
public:
    OrderProduct();
    OrderProduct(int quant, int cod_product, const string &st, const string &d, const string &client, const string &provider, int id_ord);

    int get_quantity() {
        return quantity;
    }
    int get_prod(){
        return id_product;
    }
    int get_id_ord(){
        return id_order;
    }
    string get_status(){
        return status;
    }
    string get_date(){
        return date_order;
    }
    string get_id_cust(){
        return username_cust;
    }
    string get_id_prov(){
        return username_prov;
    }

    //methods

    void add();

    void changeStatus(const string& username,const string &cod_order,const string &new_status);

    void cancel_order(const std::string &username, const std::string &cod_order, const string &us_prov);

    vector<vector<string>> select_for_provider(const string &username, int control,const string &order="users.id");
    vector<vector<string>> select_single_order_for_provider(const string &username, const string &cod_order);
    int select_count_for_provider(const string &username, int control);
    int select_count_single_order_for_provider(const string &username, const string &cod_order);

    vector<vector<string>> select_for_client(const string &username, int control, const string &order="users.id");
    vector<vector<string>> select_single_order_for_client(const string &username, const string &cod_order, const string &us_prov);
    int select_count_for_client(const string &username, int control);
    int select_count_single_order_for_client(const string &username, const string &cod_order, const string &us_prov);

    int select_id_last_order(const string &username_prov);
private:
    int quantity;
    int id_product;
    string status;
    string date_order;
    string username_cust;
    string username_prov;
    int id_order;
};

#endif // INGROSSO_ONLINE_ORDERPRODUCT_H