#ifndef PASSWORDMANAGER_WINDOW_H
#define PASSWORDMANAGER_WINDOW_H

#include <QtWidgets>
#include "login.h"
#include "mainMenu.h"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
private:
    Login *login;
    MainMenu *mainMenu;
    string masterpassword;
    void loging();
};

#endif