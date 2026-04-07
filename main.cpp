#include <QtWidgets>
#include "Qt/window.h"
#include "sqlBackend/sql.h"
#include <iostream>

void sqlTestFunction() {
    Sql sql;
    sql.openDb();
    sql.readData(20);
    sql.closeDb();
    cout << "sql test finished" << endl;
}

int main(int argc, char *argv[]) {
    bool x = false;
    if(x) {
        QApplication a(argc, argv);
        Window w;
        w.show();
        return a.exec();
    }
    else {
        sqlTestFunction();
        return 0;
    }
}