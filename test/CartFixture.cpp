
//
// Created by Matilde Tarchi on 29/05/23.
//

#include "../User.h"
#include "../Client.h"
#include "gtest/gtest.h"

class CartSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        client = make_unique<Client>("C", "andrea", "via dini", email, "psw", "Erlippe", "Firenze");
        cart = make_unique<Cart>("Erlippe");
    }

    void TearDown() override {
        cart->remove_all();
    }

    unique_ptr<Client> client;
    string email = "andrea.lipperi@icloud.com";
    unique_ptr<Cart> cart;
};

TEST_F(CartSuite, TestAddToCart) {
    cart->remove_all();
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    cart->add_product(p);
    EXPECT_EQ(1, cart->get_num_prod());
}

TEST_F(CartSuite, TestUpdateNum) {
    int n = cart->get_num_prod();
    cart->update_num(1);
    EXPECT_EQ(n+1, cart->get_num_prod());
    cart->update_num(0);
    EXPECT_EQ(n, cart->get_num_prod());
}

TEST_F(CartSuite, TestDeleteOneProd) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    cart->add_product(p);
    int num = cart->get_num_prod();
    cart->remove_one(num-1);
    EXPECT_EQ(num-1, cart->get_num_prod());
}

TEST_F(CartSuite, TestDeleteProducts) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    cart->add_product(p);
    cart->remove_all();
    EXPECT_EQ(0, cart->get_num_prod());
}
