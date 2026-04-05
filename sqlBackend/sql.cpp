#include "sql.h"

#include <iostream>

Sql::Sql() {
    dbPath = "../sqlBackend/data.db";
    sqlString = "";
    error = nullptr;
    sql = nullptr;
    rc = 0;

    openDb();
    closeDb();
}

Sql::~Sql() = default;

void Sql::openDb() {
    rc = sqlite3_open(dbPath.c_str(), &db);
    if(rc != SQLITE_OK) {
        cout << "Error opening database: " << rc << endl;
        closeDb();
        Sql::~Sql();
        exit(1);
    }
    else {
        createTable("data");
        createTable("settings");
    }
}

void Sql::closeDb() {
    sqlite3_close(db);
}

void Sql::createTable(const string &table) {
    if(table == "data")
        sqlString = "CREATE TABLE IF NOT EXISTS LOGINS (id INTEGER PRIMARY KEY AUTOINCREMENT, website TEXT, username TEXT, password TEXT, iv TEXT);";
    else if(table == "settings")
        sqlString = "CREATE TABLE IF NOT EXISTS SETTINGS (id INTEGER PRIMARY KEY AUTOINCREMENT, setting TEXT, value INT);";
    else {
        cout << "Error, unknown table: " << table << endl;
        closeDb();
        Sql::~Sql();
        exit(1);
    }
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, callback, nullptr, &error);
    if(rc != SQLITE_OK) {
        cout << "SQL error: " << error << endl;
        sqlite3_free(error);
    }
}

void Sql::insertData(const int id, const string &website, const string &username, const string &password, const string &iv) {
    sqlString = "INSERT INTO LOGINS (id,website,username,password,iv) VALUES (" + to_string(id) + ", '" + website +
                "', '" + username + "', '" + password + "', '" + iv + "');";
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, callback, nullptr, &error);
    if(rc != SQLITE_OK) {
        cout << "SQL error: " << error << endl;
        sqlite3_free(error);
        closeDb();
        Sql::~Sql();
        exit(1);
    }
}

void Sql::updateData() {}

void Sql::readData() {}

void Sql::deleteData() {}

void Sql::readTable() {}

int Sql::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i=0; i<argc; i++)
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    printf("\n");
    return 0;
}