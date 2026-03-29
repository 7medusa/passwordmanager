#include <QtWidgets>
#include "../backend/back.h"
#include "window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //back();
    Window w;
    w.show();
    return a.exec();
}