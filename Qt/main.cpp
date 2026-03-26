#include <QtWidgets>
#include "../backend/back.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    back();
    return a.exec();
}