#ifndef PASSWORDMANAGER_SQL_H
#define PASSWORDMANAGER_SQL_H

#include <sqlite3.h>

class Sql {
public:
    Sql();
    ~Sql();
private:
    void openDB();
    void closeDB();
    void createTable();
    void insertData();
    void updateData();
    void readData();
    void deleteData();
    void readTable();
    sqlite3* db;
};

#endif