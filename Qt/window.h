#ifndef PASSWORDMANAGER_WINDOW_H
#define PASSWORDMANAGER_WINDOW_H

#include <QtWidgets>
#include "login.h"
#include "mainMenu.h"
#include "entrie.h"
#include "../backend/sql.h"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
private:
    void loging();
    void entrieClicked(int id);
    void entrieExited();
    void addEntrieExited();
    void addEntrieClicked();
    QStackedWidget *stack;
    Login *login;
    MainMenu *mainMenu;
    Entrie *entrie;
    AddEntrie *addEntrie;
    ListItem *listItem;
    string masterpasswordString;
    Sql sql;

    AES_ctx ctx;
    uint8_t key[32];
    uint8_t iv[16];
};

#endif