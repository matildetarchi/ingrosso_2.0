//
// Created by Matilde Tarchi on 29/07/22.
//

#ifndef INGROSSO_ONLINE_USER_H
#define INGROSSO_ONLINE_USER_H

#define add 0
#define cancel 1
#include <string>
#include <vector>
#include "orders.h"
#include "cart.h"
#include "favourites.h"
#include "store.h"

using namespace std;
class User {
public:
    User();
    User(const std::string &t, const std::string &bn,const std::string &a, const std::string &e, const std::string &password, const std::string &us, const std::string &c);

    virtual ~User() {}

    virtual void setOrder(Orders *ord);
    virtual void setFavourites(Favourites *fav);
    virtual void setCart(Cart *crt);
    virtual void setStore(Store *st);

    const string get_type() {
        return type;
    }
    const string get_bus_name() {
        return business_name;
    }
    const string get_address() {
        return address;
    }
    const string get_city() {
        return city;
    }
    const string get_email() {
        return email;
    }
    const string get_psw() {
        return psw;
    }
    const string get_username() {
        return username;
    }
    void set_address(const string &new_addr) {
        address = new_addr;
    }
    void set_city(const string &new_city) {
        city = new_city;
    }
    void set_email(const string &new_email) {
        email = new_email;
    }
    void set_password(const string &new_psw) {
        psw= new_psw;
    }
    void set_username(const string &new_username) {
        username = new_username;
    }


    std::string username;
private:
    std::string type;
    string business_name;
    std::string address;
    std::string city;
    std::string email;
    std::string psw;
};

#endif //INGROSSO_ONLINE_USER_H