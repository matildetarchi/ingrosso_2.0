//
// Created by Andrea Lipperi on 08/05/23.
//

#include "dbCityManager.h"
#include <fstream>
#include "database.h"
#include <SQLiteCpp/Statement.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

dbCityManager::dbCityManager() {

    //metodo per creare la tabella delle categorie di prodotti nel database
    string query="CREATE TABLE IF NOT EXISTS cities (id INTEGER PRIMARY KEY autoincrement, name VARCHAR NOT NULL);";
    db.exec(query);

}

int dbCityManager::number_of_city(){

    //metodo per sapere il numero di città nel db
    int n;
    string query="SELECT count(*) FROM cities";
    n = db.execAndGet(query);
    return n;

}
std::vector<std::string> dbCityManager::select() {

    //metodo per prendere i nomi delle categorie dal db
    string city;
    std::vector<std::string> cities;

    //lancio la query
    // e inserisco i valori in un vettore di stringheche poi restituisco
    SQLite::Statement query(db, "SELECT name FROM cities");
    while (query.executeStep()) {
        city = query.getColumn(0).getString();
        cities.push_back(city);

    }
    query.reset();
    return cities;

}
