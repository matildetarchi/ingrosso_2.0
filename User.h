//
// Created by Matilde Tarchi on 29/07/22.
//

#ifndef INGROSSO_ONLINE_USER_H
#define INGROSSO_ONLINE_USER_H

#define add 0
#define cancel 1
#include <string>
#include <vector>
#include "OrdersList.h"
#include "Cart.h"
#include "Favourites.h"
#include "Store.h"

using namespace std;
class User {
public:
    User(const string &t, const string &bn,const string &a, const string &e, const string &password, const string &us, const string &c);

    virtual ~User() {}

    virtual void set_order(OrdersList *ord);
    virtual void set_favourites(Favourites *fav);
    virtual void set_cart(Cart *crt);
    virtual void set_store(Store *st);

    virtual Cart* get_cart();
    virtual Favourites* get_fav();
    virtual OrdersList* get_order();
    virtual Store* get_store();



    const string &get_type() {
        return type;
    }

    const string &get_bus_name() {
        return business_name;
    }

    const string &get_address() {
        return address;
    }

    const string &get_city() {
        return city;
    }

    const string &get_email() {
        return email;
    }

    const string &get_psw() {
        return psw;
    }

    const string &get_username() {
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

    void set_bus_name(const string &b_name){
        business_name=b_name;
    }



private:
    string type;
    string business_name;
    string address;
    string city;
    string email;
    string psw;
    string username;
};

#endif //INGROSSO_ONLINE_USER_H