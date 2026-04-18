#include <QtWidgets>
#include "Qt/window.h"
#include "backend/sql.h"
#include <iostream>
#include "backend/decrypt.h"
#include "backend/encrypt.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Window w;
    w.show();
    return a.exec();
}