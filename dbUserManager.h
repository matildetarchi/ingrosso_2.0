//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_DBUSERMANAGER_H
#define INGROSSO_ONLINE_DBUSERMANAGER_H


#include "User.h"
#include "Database.h"

#define accesso 0
#define registrazione 1

class dbUserManager {
public:

    explicit dbUserManager(shared_ptr<Database> d);


    void set_user(shared_ptr<User> us){
        user=std::move(us);
    }




    void add_to_db();
    bool access_reg(const string &email, const string &psw, int control);
    bool remove_from_db(const string &username, const string &type);
    void change_data(const string &new_address, const string &new_city, const string &new_psw, const string &new_email, const string &new_username);
    void change_psw(const string &email, const string &new_psw);
    void select_data(const string &username);
    string select_type(const string &email);
    string select_username(const string &email);
    int select_count_users(const string &type, const string &city);
    vector<shared_ptr<User>> select_users(const string &type, const string &city);

private:
    shared_ptr<User> user;
    shared_ptr<SQLite::Database> db;

};


#endif //INGROSSO_ONLINE_DBUSERMANAGER_H
