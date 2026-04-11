#include "window.h"
#include "../defines.h"
#include <iostream>

using namespace std;

Window::Window() {
    resize(1080, 1920);
    setWindowTitle("Passwordmanager");

    stack = new QStackedWidget();
    login = new Login();
    mainMenu = new MainMenu();
    entrie = new Entrie();

    stack->addWidget(login);
    stack->addWidget(mainMenu);
    stack->addWidget(entrie);
    setCentralWidget(stack);

    QObject::connect(login, &Login::passwordCorrect, this, &Window::loging);
    QObject::connect(mainMenu, &MainMenu::entrieClicked, this,  [this](int id) {entrieClicked(id);});
    QObject::connect(entrie, &Entrie::exited, this, &Window::entrieExited);

#ifndef DEBUG
    stack->setCurrentWidget(login);
    login->show();
#else
    stack->setCurrentWidget(mainMenu);
    mainMenu->show();
#endif
}

void Window::loging() {
    masterpassword = login->masterpasswordInput;
    login->hide();
    stack->setCurrentWidget(mainMenu);
    mainMenu->show();
}

void Window::entrieClicked(int id) {
    sql.openDb();
    sql.readData(id);
    sql.closeDb();
    mainMenu->hide();
    entrie->id = id;
    entrie->website = sql.websiteData.website;
    entrie->username = sql.websiteData.username;
    entrie->idText->setText(QString::fromStdString(to_string(id)));
    entrie->websiteLine->setText(QString::fromStdString(entrie->website));
    entrie->usernameLine->setText(QString::fromStdString(entrie->username));
    stack->setCurrentWidget(entrie);
    entrie->show();
}

void Window::entrieExited() {
    entrie->hide();
    stack->setCurrentWidget(mainMenu);
    mainMenu->show();
}