#ifndef PASSWORDMANAGER_SQL_H
#define PASSWORDMANAGER_SQL_H

#include <sqlite3.h>
#include <string>
#include <vector>

using namespace std;

class Sql {
public:
    Sql();
    ~Sql();
    void openDb();
    void closeDb();
    void createTable(const string &table);
    void insertData(int id, const string &website, const string &username, const string &password, const string &iv);
    void updateData();
    void readData();
    void deleteData();
    void readTable();
    vector<string> tableEntries;
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    sqlite3* db;
    string dbPath;
    string sqlString;
    int rc;
    char* sql;
    char* error;
};

#endif