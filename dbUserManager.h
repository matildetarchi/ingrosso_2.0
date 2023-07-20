//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_DBUSERMANAGER_H
#define INGROSSO_ONLINE_DBUSERMANAGER_H


#include <string>
#include <vector>
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include "database.h"
#include "user.h"

class dbUserManager {
public:
    void add_to_db();
    bool access_reg(const string &email, const string &psw, int control);
    bool remove_from_db(const string &username, const string &type);
    void changeData(const string &username_old, const string &new_address, const string &new_city, const string &new_psw, const string &new_email, const string &new_username);
    void changePsw(const string &email, const string &new_psw);
    void select_data(const string &username);
    const string select_type(const string &email);
    const string select_username(const string &email);
    vector<vector<string>> select_data_all_users(const string &type, const string &city, const string &control="users.id");
    int select_count_users(const string &type, const string &city);
private:
    User user;

};


#endif //INGROSSO_ONLINE_DBUSERMANAGER_H
