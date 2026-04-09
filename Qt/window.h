#ifndef PASSWORDMANAGER_WINDOW_H
#define PASSWORDMANAGER_WINDOW_H

#include <QtWidgets>
#include "login.h"
#include "mainMenu.h"
#include "entrie.h"
#include "../sqlBackend/sql.h"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
private:
    QStackedWidget *stack;
    Login *login;
    MainMenu *mainMenu;
    Entrie *entrie;
    ListItem *listItem;
    string masterpassword;
    Sql sql;
    void loging();
    void entrieClicked(int id);
    void entrieExited();
};

#endif