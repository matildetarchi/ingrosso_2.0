//
// Created by Andrea Lipperi on 30/03/23.
//

#include "GlobalVariables.h"

GlobalVariables::GlobalVariables() : value_username(""), value_type("") {}

GlobalVariables& GlobalVariables::GetInstance() {
    static GlobalVariables instance;
    return instance;
}

std::string GlobalVariables::GetValueUsername() {
    return value_username;
}
std::string GlobalVariables::GetValueType() {
    return value_type;
}

void GlobalVariables::SetValueUsername(std::string value_u) {
    value_username = value_u;
}
void GlobalVariables::SetValueType(std::string value_t) {
    value_type = value_t;
}