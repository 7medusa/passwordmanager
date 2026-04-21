#include "sql.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include "decrypt.h"
#include "encrypt.h"
#include "../defines.h"

StaticBypass Sql::staticBypass;

Sql::Sql() {
    dbPath = "../backend/data.db";
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
        cerr << "Error opening database: " << rc << endl;
        assert(false);
    }
    createTable("data");
    createTable("settings");
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
        cerr << "Error, unknown table: " << table << endl;
        assert(false);
    }
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, callback, nullptr, &error);
    if(rc != SQLITE_OK) {
        cerr << "SQL error: " << error << endl;
        assert(false);
    }
}

void Sql::insertData(const string &website, const string &username, const string &password, AES_ctx ctx) {
    uint8_t iv[16];
    generateIvFromTime(iv);
    sqlString = "INSERT INTO LOGINS (id,website,username,password,iv) VALUES (0, '0', '0', '0', '0');";
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, callback, nullptr, &error);
    if(rc != SQLITE_OK) {
#ifdef DEBUG
        cout << "SQL error: " << error << endl;
#endif
    }
    int id;
    idGap();
    maxIdToSet();
#ifdef DEBUG
    cout << staticBypass.idGap << endl;
#endif
    if(staticBypass.idGap > 0) {
        id = staticBypass.idGap;
    }
    else {
        id = staticBypass.maxId;
    }
    sqlString = "INSERT INTO LOGINS (id,website,username,password,iv) VALUES (" + to_string(id) + ", '" + website +
                "', '" + username + "', '" + encrypt(&password[0], ctx, iv) + "', '" + bytesToHex(iv, 16) + "');";
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, callback, nullptr, &error);
    if(rc != SQLITE_OK) {
        if(strcmp(error, "UNIQUE constraint failed: LOGINS.id") == 0 || strcmp(
               error, "UNIQUE constraint failed: LOGINS.website") == 0) {
            cout << "SQL warning: " << error << endl;
            sqlite3_free(error);
        }
        else {
            cerr << "SQL error: " << error << endl;
            assert(false);
        }
    }
}

void Sql::updateData(const string &column, const int &id, const string &value, AES_ctx ctx) {
    if(column != "website" && column != "username" && column != "password") {
        cerr << "Error, unknown column: " << column << endl;
        assert(false);
    }
    if(column != "password") {
        sqlString = "UPDATE LOGINS set " + column + "='" + value + "' where ID=" + to_string(id) + "; " \
        "SELECT * from LOGINS";
        sql = sqlString.data();
        rc = sqlite3_exec(db, sql, callback, (void*)data, &error);
        if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", error);
            assert(false);
        }
    }
    else {
        uint8_t iv[16];
        generateIvFromTime(iv);
        sqlString = "UPDATE LOGINS set password='" + encrypt(&value[0], ctx, iv) + "' where ID=" + to_string(id) + "; " \
        "SELECT * from LOGINS";
        sql = sqlString.data();
        rc = sqlite3_exec(db, sql, callback, (void*)data, &error);
        if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", error);
            assert(false);
        }
        sqlString = "UPDATE LOGINS set iv='" + bytesToHex(iv, 16) + "' where ID=" + to_string(id) + "; " \
        "SELECT * from LOGINS";
        sql = sqlString.data();
        rc = sqlite3_exec(db, sql, callback, (void*)data, &error);
        if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", error);
            assert(false);
        }
    }
}

void Sql::readData(const int &id, AES_ctx ctx) {
    sqlString = "SELECT * FROM LOGINS WHERE id=" + to_string(id) + ";";
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, saveEntrieCallback, (void*)data, &error);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", error);
        assert(false);
    }
    websiteData = staticBypass.websiteData;
    auto ivBytes = hexToBytes(websiteData.iv);
#ifdef DEBUG
    if(ivBytes.size() != 16)
        cout << "invalid IV format" << endl;
#endif
    uint8_t iv[16];
    memcpy(iv, ivBytes.data(), 16);
    websiteData.password = decrypt(websiteData.password, ctx, iv);
}

void Sql::deleteData(const int &id) {
    sqlString = "DELETE from LOGINS where ID=" + to_string(id) + ";";
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, callback, (void*)data, &error);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", error);
        assert(false);
    }
}

void Sql::readTable() {
    tableEntries.clear();
    staticBypass.tableEntries.clear();
    sqlString = "SELECT * from LOGINS";
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, saveEntriesCallback, (void*)data, &error);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", error);
        assert(false);
    }
    tableEntries = staticBypass.tableEntries;
}

int Sql::idGap() {
    sqlString = "SELECT l1.id + 1 AS fehlende_id FROM LOGINS l1 LEFT JOIN LOGINS l2 ON l2.id = l1.id + 1 WHERE l2.id IS NULL AND l1.id < (SELECT MAX(id) FROM LOGINS) ORDER BY fehlende_id;";
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, idGapCallback, (void*)data, &error);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", error);
        assert(false);
    }
    return staticBypass.idGap;
}

int Sql::maxIdToSet() {
    sqlString = "SELECT MAX(id) AS max_id FROM LOGINS;";
    sql = sqlString.data();
    rc = sqlite3_exec(db, sql, maxIdCallback, (void*)data, &error);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", error);
        assert(false);
    }
    return staticBypass.maxId;
}

int Sql::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i=0; i<argc; i++)
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    printf("\n");
    return 0;
}

int Sql::saveEntriesCallback(void *NotUsed, int argc, char **argv, char **azColName) {//returns all entries
    int id;
    string website;
    for(int i = 0; i < argc; i++) {
        if(i == 0 && argv[i] != nullptr) {
            id = atoi(argv[i]);
        }
        else if(i == 1 && argv[i] != nullptr) {
            website = argv[i];
        }
    }
    staticBypass.tableEntries.push_back({id, website});
    return 0;
}

int Sql::saveEntrieCallback(void *NotUsed, int argc, char **argv, char **azColName) {//returns only searched entries
    int id;
    string website, username, password, iv;
    for(int i = 0; i < argc; i++) {
        if(i == 0 && argv[i] != nullptr) {
            id = atoi(argv[i]);
        }
        else if(i == 1 && argv[i] != nullptr) {
            website = argv[i];
        }
        else if(i == 2 && argv[i] != nullptr) {
            username = argv[i];
        }
        else if(i == 3 && argv[i] != nullptr) {
            password = argv[i];
        }
        else if(i == 4 && argv[i] != nullptr) {
            iv = argv[i];
        }
    }
    staticBypass.websiteData = {id, website, username, password, iv};
    return 0;
}

int Sql::idGapCallback(void *NotUsed, int argc, char **argv, char **azColName) {
    staticBypass.idGap = atoi(argv[0]);
    return 0;
}

int Sql::maxIdCallback(void *NotUsed, int argc, char **argv, char **azColName) {
    if(argv[0] == nullptr) {
        staticBypass.maxId = 0;
    }
    staticBypass.maxId = atoi(argv[0]) + 1;
    return 0;
}