//
// Created by Matilde Tarchi on 08/07/23.
//

#ifndef INGROSSO_ONLINE_DATE_H
#define INGROSSO_ONLINE_DATE_H
#include <ctime>
#include <sstream>

class Date {
public:
    Date(int year, int month, int day);

    int get_day() const {
        return date_.tm_mday;
    }

    int get_month() const {
        return date_.tm_mon;
    }

    int get_year() const {
        return date_.tm_year;
    }

    string to_string(const std::string &format) const;


private:
    std::tm date_;
};


#endif //INGROSSO_ONLINE_DATE_H
