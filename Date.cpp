//
// Created by Matilde Tarchi on 08/07/23.
//

#include "Date.h"

using namespace std;


 Date::Date(int year, int month, int day) {
        date_.tm_year = year - 1900; // Anno - 1900
        date_.tm_mon = month - 1; // Mese (da 0 a 11)
        date_.tm_mday = day; // Giorno
        date_.tm_hour = 0;
        date_.tm_min = 0;
        date_.tm_sec = 0;
        date_.tm_isdst = -1; // Calcola l'ora legale
 }

 std::string Date::to_string(const std::string& format) const {
        std::stringstream ss;
        char buffer[80];
        strftime(buffer, sizeof(buffer), format.c_str(), &date_);
        ss << buffer;
        return ss.str();
 }

std::shared_ptr<Date> Date::string_to_date_converter(const std::string &date) {
    int year, month, day;

    // Creiamo uno stream di input dalla stringa
    std::istringstream iss(date);

    // Estrai i componenti della data dalla stringa
    char delimiter;
    iss >> year >> delimiter >> month >> delimiter >> day;
    std::shared_ptr<Date> dateObject = make_shared<Date>(year, month, day);

    return dateObject;
}











