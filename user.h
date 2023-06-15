//
// Created by Matilde Tarchi on 29/07/22.
//

#ifndef INGROSSO_ONLINE_USER_H
#define INGROSSO_ONLINE_USER_H
#include <string>
using namespace std;
class User {
public:
    User();
    User(const std::string &t, const std::string &bn,const std::string &a, const std::string &e, const std::string &psw, const std::string &us, int city);

    const string get_type() {
        return type;
    }
    const string get_bus_name() {
        return business_name;
    }
    const string get_address() {
        return address;
    }
    int get_city() {
        return id_city;
    }
    const string get_email() {
        return email;
    }
    const string get_psw() {
        return pass;
    }
    const string get_username() {
        return username;
    }

    //methods
    void add();
    bool access_reg(const string &email, const string &psw, int control);
    bool remove(const string &username, const string &type);
    void changeData(const string &username_old);
    void changePsw(const string &email, const string &new_psw);
    vector<string> select_data(const string &username);
    const string select_type(const string &email);
    const string select_username(const string &email);
    vector<vector<string>> select_data_all_users(const string &type, const string &city, const string &control="users.id");
    int select_count_users(const string &type, const string &city);

private:
    std::string type;
    string business_name;
    std::string address;
    int id_city;
    std::string email;
    std::string pass;
    std::string username;
};

#endif //INGROSSO_ONLINE_USER_H