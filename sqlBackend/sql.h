#ifndef PASSWORDMANAGER_SQL_H
#define PASSWORDMANAGER_SQL_H

#include <sqlite3.h>
#include <string>
#include <vector>

using namespace std;

struct WebsiteData {
    int id;
    string website;
};

class StaticBypass {
public:
    vector<WebsiteData> tableEntries;
};

class Sql {
public:
    Sql();
    ~Sql();
    void openDb();
    void closeDb();
    void createTable(const string &table);
    void insertData(int id, const string &website, const string &username, const string &password, const string &iv);
    void updateData(const string &column, const int &id, const auto &value);
    void readData();
    void deleteData();
    void readTable();
    vector<WebsiteData> tableEntries;
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    static int saveEntriesCallback(void *NotUsed, int argc, char **argv, char **azColName);
    static StaticBypass staticBypass;
    sqlite3* db;
    string dbPath;
    string sqlString;
    int rc;
    char* sql;
    char* error;
    const char* data;
};

#endif