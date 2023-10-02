//
// Created by Andrea Lipperi on 17/03/23.
//

#ifndef INGROSSO_ONLINE_DATABASE_H
#define INGROSSO_ONLINE_DATABASE_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/Database.h>
#include "sqlite3.h"

using namespace std;

class Database{
public:
    explicit Database(const string &db_name);


    shared_ptr<SQLite::Database> get_db(){
        return db;
    }

private:
    shared_ptr<SQLite::Database> db;
};


#endif //INGROSSO_ONLINE_DATABASE_H
