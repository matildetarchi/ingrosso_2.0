//
// Created by Andrea Lipperi on 08/05/23.
//

#ifndef INGROSSO_ONLINE_DBCITYMANAGER_H
#define INGROSSO_ONLINE_DBCITYMANAGER_H


#include <string>
#include <vector>
#include <fstream>
#include "Database.h"
#include "SQLiteCpp/Database.h"
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <memory>

using namespace std;
class dbCityManager {
public :

    explicit dbCityManager(shared_ptr<Database> d);
    int number_of_city();
    vector<string> select();

private:
    shared_ptr<SQLite::Database> db;
};


#endif //INGROSSO_ONLINE_DBCITYMANAGER_H
