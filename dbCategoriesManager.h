//
// Created by Andrea Lipperi on 16/11/22.
//

#ifndef INGROSSO_ONLINE_DBCATEGORIESMANAGER_H
#define INGROSSO_ONLINE_DBCATEGORIESMANAGER_H

#include <string>
#include <vector>
#include "dbCategoriesManager.h"
#include <fstream>
#include "Database.h"
#include <SQLiteCpp/Statement.h>
#include <iostream>


using namespace std;

class dbCategoriesManager {
public :
    dbCategoriesManager(SQLite::Database* d);
    int number_of_cat();
    vector<string> select();
private:
    SQLite::Database* db;
};

#endif // INGROSSO_ONLINE_DBCATEGORIESMANAGER_H