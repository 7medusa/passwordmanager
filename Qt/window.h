#ifndef PASSWORDMANAGER_WINDOW_H
#define PASSWORDMANAGER_WINDOW_H

#include <QtWidgets>
#include "login.h"
#include "mainMenu.h"
#include "entrie.h"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
private:
    Login *login;
    MainMenu *mainMenu;
    Entrie *entrie;
    ListItem *listItem;
    string masterpassword;
    void loging();
    void entrieClicked(const QString &itemText);
    void entrieExited();
};

#endif