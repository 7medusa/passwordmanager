#include "window.h"

Window::Window() {
    resize(1080, 1920);
    setWindowTitle("Passwordmanager");

    QObject::connect(login, &Login::passwordCorrect, this, &Window::loging);

    login = new Login();
    setCentralWidget(login);

    login->show();
}

void Window::loging() {
}