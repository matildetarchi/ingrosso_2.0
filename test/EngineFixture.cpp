//
// Created by Matilde Tarchi on 16/11/22.
//
#include "gtest/gtest.h"
#include "../dbUserManager.h"
#include "../User.h"
#include "../Engine.h"
#include "../Database.h"


class EngineSuite : public ::testing::Test {

protected:


    Engine* e = new Engine();
    string email = "matilde.tarchi@gmail.com";
    shared_ptr <Client> user;

    virtual void SetUp() {
        user = make_shared <Client>("C", "lola", "viao", email, "ciao", "mati", "roma");
    }

};

TEST_F(EngineSuite, TestDoRegistration) {

    EXPECT_EQ(1,e->do_registration(user));
    EXPECT_EQ(0,e->do_registration(user));
}

TEST_F(EngineSuite, TestDoLogin) {
    user->set_type("C");

    EXPECT_EQ(1,e->do_login(email, "ciao"));
    EXPECT_EQ(0,e->do_login(email, "hola"));
}

