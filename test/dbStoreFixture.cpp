
//
// Created by Matilde Tarchi on 29/05/23.
//


#include "../dbStoreManager.h"
#include "gtest/gtest.h"

class dbStoreSuite : public ::testing::Test {

protected:
    unique_ptr<Provider> provider;
    unique_ptr<Client> client;
    string emailp = "matilde.tarchi@icloud.com";
    string emailc = "dario.mori@icloud.com";
    unique_ptr<Store> store;
    shared_ptr<dbStoreManager> db_store;
    shared_ptr<Database> d;
    shared_ptr<SQLite::Database> db;

    virtual void SetUp() {
        provider = make_unique<Provider>("F", "matilde", "via dini", emailp, "pss", "Matilde", "Firenze");
        client = make_unique<Client>("C", "dario", "via dini", emailc, "psw", "Dario", "Firenze");
        const std::string dbPath = "ingrosso_2.0/database/dbStore.sqlite";
        d = make_shared <Database>(dbPath);
        store = make_unique<Store>("Matilde");
        db_store = make_shared<dbStoreManager>(d);
        db = d->get_db();
    }

    void TearDown() override {
        store->remove_all();
        db_store->remove_from_db(store->get_id());
    }

};

TEST_F(dbStoreSuite, TestAddToDb) {
    store->remove_all();
    db_store->remove_from_db(store->get_id());
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    store->add_to_store(p);
    db_store->add_to_db();
    EXPECT_EQ(1, db_store->select_count_for_provider());
}

TEST_F(dbStoreSuite, TestSelectCountForC) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    store->add_to_store(p);
    db_store->add_to_db();
    EXPECT_EQ(1, db_store->select_count_for_client("pasta", "All"));
}

TEST_F(dbStoreSuite, TestSelectCountForP) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    store->add_to_store(p);
    db_store->add_to_db();
    EXPECT_EQ(1, db_store->select_count_for_provider());
}

TEST_F(dbStoreSuite, TestRemoveOne) {
    shared_ptr <Product> p = make_shared<Product>("penne", 1.24, 5, 6, "Matilde", "pasta");
    store->add_to_store(p);
    db_store->add_to_db();
    int n = db_store->select_count_for_provider();
    db_store->remove_from_db(p->get_id_store());
    EXPECT_EQ(n-1, db_store->select_count_for_provider());
}