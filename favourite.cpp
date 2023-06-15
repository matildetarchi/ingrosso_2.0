//
// Created by Matilde Tarchi on 02/08/22.
//

#include "favourite.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Favourites::Favourites(int cod_product, const string &client, const string &provider) {

    id_product[num_prod]=cod_product;
    username_cust[num_prod]=client;
    username_prov[num_prod]=provider;
    update_num_prod();

}
