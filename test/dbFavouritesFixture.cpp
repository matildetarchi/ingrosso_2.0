
//
// Created by Matilde Tarchi on 29/05/23.
//


#include "../dbFavouritesManager.h"
#include "gtest/gtest.h"

class dbFavSuite : public ::testing::Test {

protected:
    unique_ptr<Client> client;
    string email = "dario.mori@icloud.com";
    unique_ptr<Favourites> fav;
    shared_ptr<dbFavouritesManager> db_fav;
    shared_ptr<Database> d;
    shared_ptr<SQLite::Database> db;

    virtual void SetUp() {
        client = make_unique<Client>("C", "dario", "via dini", email, "psw", "Dario", "Firenze");
        const std::string dbPath = "ingrosso_2.0/database/dbFavourites.sqlite";
        d = make_shared <Database>(dbPath);
        fav = make_unique<Favourites>("Dario");
        db_fav = make_shared<dbFavouritesManager>(d);
        db = d->get_db();
    }

    void TearDown() override {
        fav->remove_all();
        db_fav->remove_all();
    }

};

TEST_F(dbFavSuite, TestAddToDb) {
    fav->remove_all();
    db_fav->remove_all();
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    fav->add_product(p);
    db_fav->add_to_db();
    EXPECT_EQ(1, db_fav->select_count_of_prod());
}

TEST_F(dbFavSuite, TestSelectCount) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    fav->add_product(p);
    db_fav->add_to_db();
    EXPECT_EQ(1, db_fav->select_count_of_prod());
}

TEST_F(dbFavSuite, TestRemoveOne) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    fav->add_product(p);
    db_fav->add_to_db();
    int n = db_fav->select_count_of_prod();
    db_fav->remove_prod(n-1);
    EXPECT_EQ(n-1, db_fav->select_count_of_prod());
}

TEST_F(dbFavSuite, TestRemoveAll) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    fav->add_product(p);
    db_fav->add_to_db();
    db_fav->remove_all();
    EXPECT_EQ(0, fav->get_num_prod());
}
