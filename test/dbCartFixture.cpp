
//
// Created by Matilde Tarchi on 29/05/23.
//


#include "../dbCartManager.h"
#include "gtest/gtest.h"

class dbCartSuite : public ::testing::Test {

protected:
    unique_ptr<Client> client;
    string email = "dario.mori@icloud.com";
    unique_ptr<Cart> cart;
    shared_ptr<dbCartManager> db_cart;
    shared_ptr<Database> d;
    shared_ptr<SQLite::Database> db;

    virtual void SetUp() {
        client = make_unique<Client>("C", "dario", "via dini", email, "psw", "Dario", "Firenze");
        const std::string dbPath = "ingrosso_2.0/database/dbCart.sqlite";
        d = make_shared <Database>(dbPath);
        cart = make_unique<Cart>("Dario");
        db_cart = make_shared<dbCartManager>(d);
        db = d->get_db();
    }

    void TearDown() override {
        cart->remove_all();
        db_cart->remove_all();
    }

};

TEST_F(dbCartSuite, TestAddToDb) {
    cart->remove_all();
    db_cart->remove_all();
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    cart->add_product(p);
    db_cart->add_to_db();
    EXPECT_EQ(1, db_cart->select_count_of_prod());
}

TEST_F(dbCartSuite, TestSelectCount) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    cart->add_product(p);
    db_cart->add_to_db();
    EXPECT_EQ(1, db_cart->select_count_of_prod());
}

TEST_F(dbCartSuite, TestRemoveOne) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    cart->add_product(p);
    db_cart->add_to_db();
    int n = db_cart->select_count_of_prod();
    db_cart->remove_prod(n-1);
    EXPECT_EQ(n-1, db_cart->select_count_of_prod());
}

TEST_F(dbCartSuite, TestRemoveAll) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    cart->add_product(p);
    db_cart->add_to_db();
    db_cart->remove_all();
    EXPECT_EQ(0, cart->get_num_prod());
}
