//
// Created by Matilde Tarchi on 08/07/23.
//

#include "Date.h"

using namespace std;


 Date::Date(int year, int month, int day) {
        date_.tm_year = year-1900; // Anno - 1900
        date_.tm_mon = month ; // Mese (da 0 a 11)
        date_.tm_mday = day; // Giorno
        date_.tm_hour = 0;
        date_.tm_min = 0;
        date_.tm_sec = 0;
        date_.tm_wday=0;
        date_.tm_yday=0;
        date_.tm_isdst=-1; //ora legale
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

    // Creo uno stream di input dalla stringa
    std::istringstream iss(date);

    // Estraggo i componenti della data dalla stringa
    char delimiter;
    iss >> day >> delimiter >> month >> delimiter >> year;
    std::shared_ptr<Date> dateObject = make_shared<Date>(year, month, day);

    return dateObject;
}

std::shared_ptr<Date> Date::get_current_date() {

    std::time_t t = std::time(nullptr); // ottiene il numero di secondi trascorsi dal 1 gennaio 1970
    std::tm* now = std::localtime(&t); // converte in una struttura tm con informazioni sulla data e sull'ora attuali
    int year = now->tm_year + 1900; // anno attuale (tm_year contiene l'anno dal 1900)
    int month = now->tm_mon + 1; // mese attuale (tm_mon contiene il mese da 0 a 11)
    int day = now->tm_mday; // giorno attuale del mese
    std::shared_ptr<Date> date= make_shared<Date>(year, month, day);
    return date;
}











