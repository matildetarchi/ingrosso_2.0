//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_CATEGORIES_H
#define INGROSSO_ONLINE_CATEGORIES_H

#include <string>
#include <vector>
#include "categories.h"
using namespace std;
class Categories {
public :
    Categories();
    int number_of_cat();
    std::vector<std::string> select();
};

#endif // INGROSSO_ONLINE_CATEGORIES_H