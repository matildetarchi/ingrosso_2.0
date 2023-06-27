//
// Created by Andrea Lipperi on 17/03/23.
//

#ifndef INGROSSO_ONLINE_DATABASE_H
#define INGROSSO_ONLINE_DATABASE_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <SQLiteCpp/Statement.h>
#include "sqlite3.h"
#include "SqliteDB.h"

//questa pagina contiene l'indirizzo del database sqlite su cui
//lavorerà il programmaııı
using namespace std;

class Database{
public:
    Database(string db_name);
    ~Database();

    SQLite::Database* get_db(){
        return db;
    }

private:
    SQLite::Database* db;
};


#endif //INGROSSO_ONLINE_DATABASE_H
