//
// Created by Andrea Lipperi on 08/05/23.
//

#ifndef INGROSSO_ONLINE_DBCITYMANAGER_H
#define INGROSSO_ONLINE_DBCITYMANAGER_H


#include <string>
#include "dbCityManager.h"
#include <vector>
#include <fstream>
#include "Database.h"
#include <SQLiteCpp/Statement.h>
#include <iostream>

class dbCityManager {
public :

    dbCityManager(SQLite::Database *d);
    int number_of_city();
    std::vector<std::string> select();

private:
    SQLite::Database* db;
};


#endif //INGROSSO_ONLINE_DBCITYMANAGER_H
