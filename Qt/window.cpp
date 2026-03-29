#include "window.h"

Window::Window() {
    resize(1080, 1920);
    setWindowTitle("Passwordmanager");

    login = new Login();
    mainMenu = new MainMenu();

    QObject::connect(login, &Login::passwordCorrect, this, &Window::loging);

    setCentralWidget(login);
    login->show();
}

void Window::loging() {
    masterpassword = login->masterpasswordInput;
    login->hide();
    setCentralWidget(mainMenu);
    mainMenu->show();
}