#include "window.h"
#include "../defines.h"
#include <iostream>
#include "../backend/encrypt.h"

using namespace std;

Window::Window() {
    resize(1080, 1920);
    setWindowTitle("Passwordmanager");

    stack = new QStackedWidget();
    login = new Login();
    mainMenu = new MainMenu();
    entrie = new Entrie(ctx);
    addEntrie = new AddEntrie(ctx);

    stack->addWidget(login);
    stack->addWidget(mainMenu);
    stack->addWidget(entrie);
    stack->addWidget(addEntrie);
    setCentralWidget(stack);

    QObject::connect(login, &Login::passwordCorrect, this, &Window::loging);
    QObject::connect(mainMenu, &MainMenu::entrieClicked, this,  [this](int id) {entrieClicked(id);});
    QObject::connect(mainMenu, &MainMenu::addEntrieClicked, this, &Window::addEntrieClicked);
    QObject::connect(entrie, &Entrie::exited, this, &Window::entrieExited);
    QObject::connect(addEntrie, &AddEntrie::addEntrieExited, this, &Window::addEntrieExited);


#ifndef DEBUG
    stack->setCurrentWidget(login);
    login->show();
#else
    masterpasswordString = "hello";//test masterpassword
    generateIvFromTime(iv);
    char* masterPassword = new char[masterpasswordString.length() + 1];
    strcpy(masterPassword, masterpasswordString.c_str());
    keyFromMasterPassword(masterPassword, key);
    delete[] masterPassword;
    AES_init_ctx_iv(&ctx, key, iv);

    stack->setCurrentWidget(mainMenu);
    mainMenu->show();
#endif
}

void Window::loging() {
    mainMenu->addEntrie();
    masterpasswordString = login->masterpasswordInput;
    login->hide();
    stack->setCurrentWidget(mainMenu);
    mainMenu->show();

    generateIvFromTime(iv);
    char* masterPassword = new char[masterpasswordString.length() + 1];
    strcpy(masterPassword, masterpasswordString.c_str());
    keyFromMasterPassword(masterPassword, key);
    delete[] masterPassword;
    AES_init_ctx_iv(&ctx, key, iv);
}

void Window::entrieClicked(int id) {
    sql.openDb();
    sql.readData(id, ctx);
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
    mainMenu->entrieUpdate();
    entrie->hide();
    stack->setCurrentWidget(mainMenu);
    mainMenu->show();
    mainMenu->search->setText("");
}

void Window::addEntrieExited() {
    mainMenu->entrieUpdate();
    addEntrie->hide();
    stack->setCurrentWidget(mainMenu);
    mainMenu->show();
}

void Window::addEntrieClicked() {
    mainMenu->hide();
    stack->setCurrentWidget(addEntrie);
    addEntrie->show();
}