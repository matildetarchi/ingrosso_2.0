//
// Created by Matilde Tarchi on 08/07/23.
//

#ifndef INGROSSO_ONLINE_DATE_H
#define INGROSSO_ONLINE_DATE_H
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <memory>

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

    std::string to_string(const std::string &format) const;

    static std::shared_ptr<Date> string_to_date_converter(const std::string &date);

    static std::shared_ptr<Date> get_current_date();

private:
    std::tm date_;
};


#endif //INGROSSO_ONLINE_DATE_H
