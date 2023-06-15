//
// Created by Andrea Lipperi on 08/05/23.
//

#ifndef INGROSSO_ONLINE_CITY_H
#define INGROSSO_ONLINE_CITY_H


#include <string>
#include "city.h"
#include <vector>
class City {
public :
    City();
    int number_of_city();
    std::vector<std::string> select();
};


#endif //INGROSSO_ONLINE_CITY_H
