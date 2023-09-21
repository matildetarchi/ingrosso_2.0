//
// Created by Matilde Tarchi on 16/11/22.
//
#include "gtest/gtest.h"
#include "../cart.h"
#include "../User.h"
#include "../Client.h"
#include "../Provider.h"


class UserSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        client = make_unique<Client>("C", "dario", "via dini", email, "psw", "Dario", "Firenze");
        provider = make_unique<Provider>("P", "siria", "via dini", "siria.mazzocchi@icloud.it", "psw", "Sisi", "Firenze");
    }

    void TearDown() override {
        client->delete_objects_of_user();
        provider->delete_objects_of_user();
    }

    unique_ptr<Client> client;
    unique_ptr<Provider> provider;
    string email = "dario.mori@gmail.com";
};


TEST_F(UserSuite, TestClientAddToCart) {
    unique_ptr<Cart> c = make_unique<Cart>("Dario");
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Siria", "pasta");
    client->add_to_cart(p);
    EXPECT_EQ(1, c->get_num_prod());
}

TEST_F(UserSuite, TestClientAddToFav) {
    unique_ptr<Favourites> f = make_unique<Favourites>("Dario");
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Siria", "pasta");
    client->add_to_fav(p);
    EXPECT_EQ(1, f->get_num_prod());
}

TEST_F(UserSuite, TestClientRemoveFromCart) {
    unique_ptr<Cart> c = make_unique<Cart>("Dario");
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Siria", "pasta");
    client->add_to_cart(p);
    EXPECT_EQ(1, c->get_num_prod());
    int id = p->get_id_store();
    client->remove_from_cart(id);
    EXPECT_EQ(0, c->get_num_prod());
}

TEST_F(UserSuite, TestClientRemoveFromFav) {
    unique_ptr<Favourites> f = make_unique<Favourites>("Dario");
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Siria", "pasta");
    client->add_to_fav(p);
    EXPECT_EQ(1, f->get_num_prod());
    int id = p->get_id_store();
    client->remove_from_fav(id);
    EXPECT_EQ(0, f->get_num_prod());
}

TEST_F(UserSuite, TestClientDeleteAll) {
    //trova un modo per testarla
}

TEST_F(UserSuite, TestProviderAddProd) {
    unique_ptr<Store> s = make_unique<Store>("Sisi");
    provider->add_prod("penne", 1.24, 5, 6, "Siria", "pasta");
    EXPECT_EQ(1, s->get_num_prod());
}

TEST_F(UserSuite, TestProviderModifyProd) {
    unique_ptr<Store> s = make_unique<Store>("Sisi");
    provider->add_prod("penne", 1.24, 5, 6, "Siria", "pasta");
    EXPECT_EQ(1, provider->modify_prod(s->get_id(), "fusilli", 1.25, 7));
    EXPECT_EQ(0, provider->modify_prod(100, "fusilli", 1.25, 7));
}

TEST_F(UserSuite, TestProviderDeleteAll) {
    //come sopra
}

