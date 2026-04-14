#include <QtWidgets>
#include "Qt/window.h"
#include "backend/sql.h"
#include <iostream>

void sqlTestFunction() {
    Sql sql;
    sql.openDb();
    sql.insertData("searchh", "searchh", "searchh", "searchh");
    sql.closeDb();
    cout << "sql test finished" << endl;
}

int main(int argc, char *argv[]) {
    bool x = true;
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