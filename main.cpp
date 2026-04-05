#include <QtWidgets>
#include "Qt/window.h"
#include "sqlBackend/sql.h"
#include <iostream>

void sqlTestFunction() {
    Sql sql;
    sql.openDb();
    sql.insertData(0, "website", "username", "password", "iv");
    sql.closeDb();
    cout << "sql test finished" << endl;
}

int main(int argc, char *argv[]) {
    //QApplication a(argc, argv);
    //Window w;
    //w.show();

    sqlTestFunction();

    return 0;
    //return a.exec();
}