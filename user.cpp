//
// Created by Andrea Lipperi on 14/11/22.
//

#include "user.h"
#include <string>
using namespace std;

User::User(const std::string &t, const std::string &bn,const std::string &a, const std::string &e, const std::string &password, const std::string &us, const std::string &c){
    type = t;
    business_name= bn;
    address = a;
    city = c;
    email = e;
    psw = password;
    username = us;
}

