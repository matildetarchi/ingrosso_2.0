//
// Created by Andrea Lipperi on 17/03/23.
//
#include "database.h"


Database::Database(string db_name){
    db=new SQLite::Database(db_name);
}
