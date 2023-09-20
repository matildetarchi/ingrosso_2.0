
//
// Created by Matilde Tarchi on 29/05/23.
//

#include "../store.h"
#include "../Client.h"
#include "../Provider.h"
#include "../Order.h"
#include "../OrdersList.h"
#include "gtest/gtest.h"

class OrderSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        o = make_unique<Order>(1, "S", "Dario");
        o1 = make_unique<OrdersList>("Dario");
        client = make_unique<Client>("C", "dario", "via dini", email, "psw", "Dario", "Firenze");
        provider = make_unique<Provider>("P", "siria", "via dini", "siria.mazzocchi@icloud.it", "psw", "Sisi", "Firenze");

    }

    void TearDown() override {
        o->remove_all();
        o1->remove_all();
    }

    unique_ptr<Client> client;
    unique_ptr<Provider> provider;
    string email = "dario.mori@icloud.com";
    shared_ptr<OrdersList> o1;
    shared_ptr<Order> o;
};

TEST_F(OrderSuite, TestAddOrder) {
    o->remove_all();
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    o->add_to_order(p);
    EXPECT_EQ(1, o->get_num_prod());
}

TEST_F(OrderSuite, TestAddToOL) {
    int num = o1->get_num_order();
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    o->add_to_order(p);
    o1->add_order(o);
    EXPECT_EQ(num+1, o1->get_num_order());
}

TEST_F(OrderSuite, TestUpdateNumOL) {
    int n = o1->get_num_order();
    o1->update_num(1);
    EXPECT_EQ(n+1, o1->get_num_order());
    o1->update_num(0);
    EXPECT_EQ(n, o1->get_num_order());
}

TEST_F(OrderSuite, TestUpdateNumOrders) {
    int n = o->get_num_prod();
    o->update_num(1);
    EXPECT_EQ(n+1, o->get_num_prod());
    o->update_num(0);
    EXPECT_EQ(n, o->get_num_prod());
}

TEST_F(OrderSuite, TestGetTotal) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    o->add_to_order(p);
    shared_ptr <Product> p1 = make_shared<Product>("fusilli", 1.25, 5, 6, "Erlippe", "pasta");
    o->add_to_order(p1);
    double tot = (1.24*5) + (1.25*5);
    EXPECT_EQ(tot, o->get_total(o));
}

TEST_F(OrderSuite, TestModifyStatus) {
    shared_ptr<Order> ord = make_shared<Order>(1, "S", "Dario");
    o1->add_order(ord);
    EXPECT_EQ(0, o1->modify_status(2, "A"));
    EXPECT_EQ(1, o1->modify_status(1, "A"));
}

TEST_F(OrderSuite, TestDeleteOneFromOL) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    o->add_to_order(p);
    o1->add_order(o);
    o1->remove_one(1);
    EXPECT_EQ(0, o1->get_num_order());
}

TEST_F(OrderSuite, TestDeleteAllFromOL) {
    o1->remove_all();
    EXPECT_EQ(0, o1->get_num_order());
}

TEST_F(OrderSuite, TestDeleteOneProd) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    o->add_to_order(p);
    o->remove_one(1);
    EXPECT_EQ(0, o->get_num_prod());
}

TEST_F(OrderSuite, TestDeleteProducts) {
    o->remove_all();
    EXPECT_EQ(0, o->get_num_prod());
}