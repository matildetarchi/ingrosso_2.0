//
// Created by Andrea Lipperi on 17/03/23.
//
/*
#ifndef INGROSSO_ONLINE_DATABASE_H
#define INGROSSO_ONLINE_DATABASE_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/Database.h>
#include "sqlite3.h"

//questa pagina contiene l'indirizzo del database sqlite su cui
//lavorerà il programmaııı
using namespace std;

class Database{
public:
    explicit Database(string db_name);
    ~Database();

    SQLite::Database* get_db(){
        return db;
    }

private:
    SQLite::Database* db;
};


#endif //INGROSSO_ONLINE_DATABASE_H
*/