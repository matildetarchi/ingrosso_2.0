//
// Created by Matilde Tarchi on 29/07/22.
//

#ifndef INGROSSO_ONLINE_USER_H
#define INGROSSO_ONLINE_USER_H


#include "OrdersList.h"
#include "Cart.h"
#include "Favourites.h"
#include <utility>


using namespace std;
class User {
public:
    User();
    User( const string &t, const string &bn,const string &a, const string &e, const string &password, const string &us, const string &c);

    virtual ~User() = default;


    shared_ptr<OrdersList> get_order_list(){
        return order;
    };



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

    const int &get_db_id() const {
        return db_id;
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

    void set_id_db(const int &id){
        db_id=id;
    }
    void set_type(const string &t){
        type=t;
    }

    virtual void delete_objects_of_user();



    virtual shared_ptr<Cart> get_cart() = 0;

    virtual shared_ptr<Favourites> get_fav() = 0;


    virtual void add_to_cart(shared_ptr<Product> p) = 0;
    virtual  void add_to_fav(shared_ptr<Product> p) = 0;
    virtual bool remove_from_cart(int id_prod) = 0;
    virtual bool remove_from_fav(int id_prod) = 0;


    virtual shared_ptr<Store> get_store()  = 0;
    virtual bool modify_prod (int id_store, string desc, double price, int a_q ) = 0;
    virtual bool add_prod(const string& desc, double price, int quantity, int a_quantity, const string&  username_prov, const string& sub_category) = 0;

private:
    string type;
    string business_name;
    string address;
    string city;
    string email;
    string psw;
    string username;
    int db_id;
    shared_ptr <OrdersList> order;
    shared_ptr <Cart> cart;
    shared_ptr <Favourites> fav;
    shared_ptr <Store> store;

};

#endif //INGROSSO_ONLINE_USER_H