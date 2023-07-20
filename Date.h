//
// Created by Matilde Tarchi on 08/07/23.
//

#ifndef INGROSSO_ONLINE_DATE_H
#define INGROSSO_ONLINE_DATE_H


class Date {
public:
    Date(int y, int m, int d);

    int get_day() const {
        return day;
    }

    int get_month() const {
        return month;
    }

    int get_year() const {
        return year;
    }

private:
    int day;
    int month;
    int year;

};


#endif //INGROSSO_ONLINE_DATE_H
