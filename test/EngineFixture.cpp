//
// Created by Matilde Tarchi on 16/11/22.
//
#include "gtest/gtest.h"
#include "../Engine.h"



class EngineSuite : public ::testing::Test {

protected:
    Engine* eng = new Engine();
    string email = "matilde.tarchi@gmail.com";
    shared_ptr <Client> user;
    shared_ptr<dbUserManager> db_user;


    virtual void SetUp() {
        db_user = eng->get_db_user();
        user = make_shared <Client>("C", "matilde tarchi", "via ciao", email, "ciao", "Mati", "Roma");
    }

};

TEST_F(EngineSuite, TestDoRegistration) {
    db_user->remove_user("Mati");
    EXPECT_EQ(1,eng->do_registration(user));
    EXPECT_EQ(0,eng->do_registration(user));
}

TEST_F(EngineSuite, TestDoLogin) {
    EXPECT_EQ(1,eng->do_login(email, "ciao"));
    EXPECT_EQ(0,eng->do_login(email, "hola"));
}

