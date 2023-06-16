//
// Created by Matilde Tarchi on 29/07/22.
//

#ifndef INGROSSO_ONLINE_FAVOURITES_H
#define INGROSSO_ONLINE_FAVOURITES_H

#include <string>
#define add 0
#define remove 1
using namespace std;
class Favourites{
public:
    Favourites();
    Favourites(const string &desc_product, double price, const string &client, const string &provider);

    const string get_prod(int index){
        return desc_prod[index];
    }
    double get_price(int index){
        return price_prod[index];
    }
    string get_cust(){
        return username_cust;
    }
    string get_prov(int index){
        return username_prov[index];
    }
    int get_num_prod(){
        return num_prod;
    }
    void update_num_prod(int control) {
        if (control==add) {
            num_prod = num_prod + 1;
        } else if (control==remove) {
            num_prod=num_prod-1;
        }
    }

    void remove_one(int index);

private :

    std::vector<string> desc_prod;
    std::vector<double> price_prod;
    string username_cust;
    vector<string> username_prov;
    int num_prod;

};

#endif //INGROSSO_ONLINE_FAVOURITES_H
