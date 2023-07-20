//
// Created by Andrea Lipperi on 30/03/23.
//

#include "GlobalVariables.h"

using namespace std;
GlobalVariables::GlobalVariables() : value_username(""), value_type("") {}

GlobalVariables& GlobalVariables::GetInstance() {
    static GlobalVariables instance;
    return instance;
}

string GlobalVariables::GetValueUsername() {
    return value_username;
}
string GlobalVariables::GetValueType() {
    return value_type;
}

void GlobalVariables::SetValueUsername(string value_u) {
    value_username = value_u;
}
void GlobalVariables::SetValueType(string value_t) {
    value_type = value_t;
}