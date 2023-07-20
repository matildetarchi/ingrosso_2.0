//
// Created by Andrea Lipperi on 08/05/23.
//

#ifndef INGROSSO_ONLINE_DBCITYMANAGER_H
#define INGROSSO_ONLINE_DBCITYMANAGER_H


#include <string>
#include "dbCityManager.h"
#include <vector>
class dbCityManager {
public :
    dbCityManager();
    int number_of_city();
    std::vector<std::string> select();
};


#endif //INGROSSO_ONLINE_DBCITYMANAGER_H
