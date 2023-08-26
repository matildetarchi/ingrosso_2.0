//
// Created by Matilde Tarchi on 16/06/23.
//

#include "Provider.h"

using namespace std;

Provider::Provider():User(){};

Provider::Provider(int id, const string &t, const string &bn,const string &a, const string &e,
                const string &password, const string &us, const string &c) : User(id, t, bn, a, e, password, us, c){

    order = make_unique<OrdersList>(us);
    store = make_unique<Store>(us);
}

Provider::~Provider() {

}

void Provider::accept_order(int id_order) {
    db_order->change_status("A", id_order);
}

void Provider::denied_order(int id_order) {
    db_order->change_status("D", id_order);
}

