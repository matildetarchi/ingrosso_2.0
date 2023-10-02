//
 // Created by dario on 16/06/2023.
//

#include "Engine.h"

Engine::Engine() {

    // Specifica del percorso del database
    const std::string dbPath = "/Users/matildetarchi/CLionProjects/ingrosso_2.0/database/ingrossodb.sqlite";
    database = make_shared <Database>(dbPath);



    db_cart = make_shared<dbCartManager>(database);
    db_store = make_shared<dbStoreManager>(database);
    db_order = make_shared<dbOrdersManager>(database);
    db_fav = make_shared<dbFavouritesManager>(database);
    db_user = make_shared<dbUserManager>(database);
    db_cate = make_shared<dbCategoriesManager>(database);
    db_subc = make_shared<dbSubcategoriesManager>(database);
    db_city = make_shared<dbCityManager>(database);
    
}

bool Engine::do_registration(const shared_ptr<User>& u) {


    string psw = u->get_psw();
    string email = u->get_email();
    if( db_user->access_reg(email,psw,1)){
        db_user->set_user(u);
        db_user->add_to_db();

        return true;
    }else
        return false;
}

bool Engine::do_login(const string &email, const string &psw) {

    if(db_user->access_reg(email, psw, 0)) {

        string username = db_user->select_username(email);
        type = db_user->select_type(email);

        if(type == "C") {

            client = make_shared<Client>(username);
            db_user->set_user(client);
            db_user->select_data(username);


            db_cart->set_user(client);
            db_cart->set_cart();
            db_cart->select();

            db_fav->set_user(client);
            db_fav->set_fav();
            db_fav->select();

            db_order->set_user(client);
            db_order->set_orderlist();
            db_order->select_for_client();

        } else {
            prov = make_shared<Provider>(username);
            db_user->set_user(prov);
            db_user->select_data(username);

            db_store->set_user(prov);
            db_store->set_store();
            db_store->set_prod_list();
            db_store->select_for_prov();


            db_order->set_user(prov);
            db_order->set_orderlist();
            db_order->select_for_provider();

        }
        return true;
    } else
        return false;
}

shared_ptr<User> Engine::get_user() {
    if(type == "C")
        return client;
    else
        return prov;
}
