//
// Created by Andrea Lipperi on 16/03/23.
//

#ifndef INGROSSO_ONLINE_DBSUBCATEGORIESMANAGER_H
#define INGROSSO_ONLINE_DBSUBCATEGORIESMANAGER_H

#include "dbCategoriesManager.h"
#include <string>
#include "database.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/Statement.h>
#include <iostream>

using namespace std;
class dbSubcategoriesManager{
public:
    dbSubcategoriesManager();
    std::vector<std::string> select(const string &categories_name);
};

#endif //INGROSSO_ONLINE_DBSUBCATEGORIESMANAGER_H
