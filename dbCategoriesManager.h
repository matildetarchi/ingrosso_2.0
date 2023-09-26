//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_DBCATEGORIESMANAGER_H
#define INGROSSO_ONLINE_DBCATEGORIESMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include "Database.h"
#include <memory>


using namespace std;

class dbCategoriesManager {
public :
    explicit dbCategoriesManager(const shared_ptr<Database>& d);

    int number_of_cat();
    vector<string> select();

private:
    shared_ptr<SQLite::Database> db;
};

#endif // INGROSSO_ONLINE_DBCATEGORIESMANAGER_H