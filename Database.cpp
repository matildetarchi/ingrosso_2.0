//
// Created by Andrea Lipperi on 17/03/23.
//

#include "Database.h"


Database::Database(const string &db_name){
    const std::string &dbPath = db_name;

    // Apro il database
    db = make_shared <SQLite::Database>(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    std::cout << "Database aperto con successo." << std::endl;
}


