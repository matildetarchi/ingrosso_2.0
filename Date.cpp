//
// Created by Matilde Tarchi on 08/07/23.
//

#include "Date.h"

using namespace std;



Date::Date(int day, int month, int year) {


}

void Date::set_date() {
    time_t now = time(0);

    tm* localTime = localtime(&now);

    year = 1900+localTime->tm_year;
    month = 1+localTime->tm_mon;
    day = localTime->tm_mday;

}



