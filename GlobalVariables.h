//
// Created by Andrea Lipperi on 30/03/23.
//

#ifndef INGROSSO_ONLINE_GLOBALVARIABLES_H
#define INGROSSO_ONLINE_GLOBALVARIABLES_H

#include <string>

//questa classe contiene i metodi per salvare globalmente
//l'username e il tipo dell'utente che sta usando il programma
class GlobalVariables {
public:
    static GlobalVariables& GetInstance();
    std::string GetValueType();
    std::string GetValueUsername();
    void SetValueUsername(std::string value_u);
    void SetValueType(std::string value_t);
private:
    GlobalVariables();
    GlobalVariables(const GlobalVariables&) = delete;
    GlobalVariables& operator=(const GlobalVariables&) = delete;
    std::string value_username;
    std::string value_type;
};


#endif //INGROSSO_ONLINE_GLOBALVARIABLES_H
