//
// Created by Andrea Lipperi on 08/05/23.
//

#ifndef INGROSSO_ONLINE_DBCITYMANAGER_H
#define INGROSSO_ONLINE_DBCITYMANAGER_H


#include <string>
#include "dbCityManager.h"
#include <vector>
#include <fstream>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>
#include <iostream>

using namespace std;
class dbCityManager {
public :

    explicit dbCityManager(SQLite::Database *d);
    int number_of_city();
    vector<string> select();

private:
    SQLite::Database* db;
};


#endif //INGROSSO_ONLINE_DBCITYMANAGER_H
