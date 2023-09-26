//
// Created by Matilde Tarchi on 29/05/23.
//

#include "../store.h"
#include "../User.h"
#include "../Product.h"
#include "../Provider.h"
#include "gtest/gtest.h"

class StoreSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        //deve essere un fornitore
        user = make_unique<Provider>("F", "matilde", "via dini", email, "psw", "Mama", "Firenze");
        store = make_unique<Store>("Mama");
    }

    void TearDown() override {
        store->remove_all();
    }

    unique_ptr<Provider> user;
    string email = "matilde.tarchi@icloud.com";
    unique_ptr<Store> store;

};

TEST_F(StoreSuite, TestAddToStore) {
    store->remove_all();
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    store->add_to_store(p);
    EXPECT_EQ(1, store->get_num_prod());
}

TEST_F(StoreSuite, TestUpdateNum) {
    int n = store->get_num_prod();
    store->update_num(0);
    EXPECT_EQ(n+1, store->get_num_prod());
    store->update_num(1);
    EXPECT_EQ(n, store->get_num_prod());
}

TEST_F(StoreSuite, TestDeleteOneProd) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    store->add_to_store(p);
    int num = store->get_num_prod();
    store->remove_one(num-1);
    EXPECT_EQ(0, store->get_num_prod());
}

TEST_F(StoreSuite, TestDeleteProducts) {
    store->remove_all();
    EXPECT_EQ(0, store->get_num_prod());
}
