#include "window.h"
#include <iostream>

Window::Window() {
    resize(1080, 1920);
    setWindowTitle("Passwordmanager");

    login = new Login();
    mainMenu = new MainMenu();
    entrie = new Entrie();

    QObject::connect(login, &Login::passwordCorrect, this, &Window::loging);
    QObject::connect(mainMenu, &MainMenu::entrieClicked, this,  [this](int id) {
        entrieClicked(id);
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

void Window::entrieClicked(int id) {
    sql.openDb();
    sql.readData(id);
    sql.closeDb();
    cout << sql.websiteData.website << endl;
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