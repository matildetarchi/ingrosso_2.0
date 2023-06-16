//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_DBCATEGORIESMANAGER_H
#define INGROSSO_ONLINE_DBCATEGORIESMANAGER_H

#include <string>
#include <vector>
#include "dbCategoriesManager.h"
using namespace std;
class dbCategoriesManager {
public :
    dbCategoriesManager();
    int number_of_cat();
    std::vector<std::string> select();
};

#endif // INGROSSO_ONLINE_DBCATEGORIESMANAGER_H