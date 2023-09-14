//
// Created by Andrea Lipperi on 16/03/23.
//

#ifndef INGROSSO_ONLINE_DBSUBCATEGORIESMANAGER_H
#define INGROSSO_ONLINE_DBSUBCATEGORIESMANAGER_H

#include "dbCategoriesManager.h"
#include <string>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <memory>
#include "Database.h"

using namespace std;
class dbSubcategoriesManager{
public:
    explicit dbSubcategoriesManager(shared_ptr<Database> d);

    vector<string> select(const string &categories_name);
    int number_of_subcat(const string &categories_name);
private:
    shared_ptr<SQLite::Database> db;
};

#endif //INGROSSO_ONLINE_DBSUBCATEGORIESMANAGER_H
