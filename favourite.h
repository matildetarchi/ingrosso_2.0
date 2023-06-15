//
// Created by Matilde Tarchi on 29/07/22.
//

#ifndef INGROSSO_ONLINE_FAVOURITE_H
#define INGROSSO_ONLINE_FAVOURITE_H

#include <string>
#define add 0
#define remove 1
using namespace std;
class Favourites{
public:
    Favourites(int cod_product, const string &client, const string &provider);

    int get_id_store(int index){
        return id_product[index];
    }
    string get_cust(int index){
        return username_cust[index];
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



private :

  std::vector<int> id_product;
  vector<string> username_cust;
  vector<string> username_prov;
  int num_prod;

};

#endif //INGROSSO_ONLINE_FAVOURITE_H
