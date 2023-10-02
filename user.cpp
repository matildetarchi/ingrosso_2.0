//
// Created by Andrea Lipperi on 14/11/22.
//

#include "User.h"
using namespace std;


User::User(const string &us){
    order = make_shared<OrdersList>(us);
}
User::User( const string &t, const string &bn,const string &a, const string &e, const string &password, const string &us, const string &c) {

    type = t;
    business_name = bn;
    address = a;
    city = c;
    email = e;
    psw = password;
    username = us;
    order = make_shared<OrdersList>(us);

}

void User::delete_objects_of_user() {
        order->remove_all();
}
