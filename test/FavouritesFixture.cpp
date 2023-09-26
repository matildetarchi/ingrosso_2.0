
//
// Created by Matilde Tarchi on 29/05/23.
//

#include "../favourites.h"
#include "../User.h"
#include "../Client.h"
#include "gtest/gtest.h"

class FavouritesSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        client = make_unique<Client>("C", "andrea", "via dini", email, "psw", "Erlippe", "Firenze");
        fav = make_unique<Favourites>("Erlippe");
    }

    void TearDown() override {
        fav->remove_all();
    }

    unique_ptr<Client> client;
    string email = "andrea.lipperi@icloud.com";
    unique_ptr<Favourites> fav;
};

TEST_F(FavouritesSuite, TestAddToFav) {
    fav->remove_all();
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    fav->add_product(p);
    EXPECT_EQ(1, fav->get_num_prod());
}

TEST_F(FavouritesSuite, TestUpdateNum) {
    int n = fav->get_num_prod();
    fav->update_num_prod(0);
    EXPECT_EQ(n+1, fav->get_num_prod());
    fav->update_num_prod(1);
    EXPECT_EQ(n, fav->get_num_prod());
}

TEST_F(FavouritesSuite, TestDeleteOneProd) {
    int num = fav->get_num_prod();
    fav->remove_one(num-1);
    EXPECT_EQ(num, fav->get_num_prod());
}

TEST_F(FavouritesSuite, TestDeleteProducts) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Erlippe", "pasta");
    fav->add_product(p);
    fav->remove_all();
    EXPECT_EQ(0, fav->get_num_prod());
}
