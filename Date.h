//
// Created by Matilde Tarchi on 08/07/23.
//

#ifndef INGROSSO_ONLINE_DATE_H
#define INGROSSO_ONLINE_DATE_H
#include <ctime>
#include <sstream>

class Date {
public:
    Date(int day, int month, int year);

    int get_day() const {
        return day;
    }

    int get_month() const {
        return month;
    }

    int get_year() const {
        return year;
    }
    Date *get_date(){
        return date;
    }
    void set_date();

    // Sovrascrittura dell'operatore <<
    friend std::ostream& operator<<(std::ostream& os, const Date& data) {
        os << data.day << "/" << data.month << "/" << data.year;
        return os;
    }

private:
    int day;
    int month;
    int year;
    Date* date;

};


#endif //INGROSSO_ONLINE_DATE_H
