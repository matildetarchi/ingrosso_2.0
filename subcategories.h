//
// Created by Andrea Lipperi on 16/03/23.
//

#ifndef INGROSSO_ONLINE_SUBCATEGORIES_H
#define INGROSSO_ONLINE_SUBCATEGORIES_H

#include "categories.h"
#include <string>
using namespace std;
class Subcategories{
public:
    Subcategories();
    std::vector<std::string> select(const string &categories_name);
};

#endif //INGROSSO_ONLINE_SUBCATEGORIES_H
