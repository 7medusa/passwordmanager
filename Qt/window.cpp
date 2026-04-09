#include "window.h"
#include <iostream>

Window::Window() {
    resize(1080, 1920);
    setWindowTitle("Passwordmanager");

    login = new Login();
    mainMenu = new MainMenu();
    entrie = new Entrie();

    QObject::connect(login, &Login::passwordCorrect, this, &Window::loging);
    QObject::connect(mainMenu, &MainMenu::entrieClicked, this,  [this](const QString &itemText) {
        entrieClicked(itemText);
    });

    setCentralWidget(login);
    login->show();
}

void Window::loging() {
    masterpassword = login->masterpasswordInput;
    login->hide();
    setCentralWidget(mainMenu);
    mainMenu->show();
}

void Window::entrieClicked(const QString &itemText) {
    /*
    mainMenu->hide();
    setCentralWidget(entrie);
    entrie->show();
    */
}

void Window::entrieExited() {
    entrie->hide();
    mainMenu->show();
    setCentralWidget(mainMenu);
}