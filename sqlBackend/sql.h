#ifndef PASSWORDMANAGER_SQL_H
#define PASSWORDMANAGER_SQL_H

#include <sqlite3.h>
#include <string>
#include <vector>

using namespace std;

struct WebsiteDataName {
    int id;
    string website;
};

struct WebsiteData {
    int id;
    string website;
    string username;
    string password;
    string iv;
};

class StaticBypass {
public:
    vector<WebsiteDataName> tableEntries;
    WebsiteData websiteData;
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
    void readData(const int &id);
    void deleteData(const int &id);
    void readTable();
    vector<WebsiteDataName> tableEntries;
    WebsiteData websiteData;
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    static int saveEntriesCallback(void *NotUsed, int argc, char **argv, char **azColName);
    static int saveEntrieCallback(void *NotUsed, int argc, char **argv, char **azColName);
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