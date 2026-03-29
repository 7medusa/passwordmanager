#ifndef PASSWORDMANAGER_WINDOW_H
#define PASSWORDMANAGER_WINDOW_H

#include <QtWidgets>
#include "login.h"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
    void loging();
private:
    Login *login;
};

#endif