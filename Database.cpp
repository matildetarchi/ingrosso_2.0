//
// Created by Andrea Lipperi on 17/03/23.
//
#include "Database.h"


Database::Database(string db_name){
    db=new SQLite::Database(db_name);
}
//TODO è ok?
Database::~Database() {
    delete db;
}
