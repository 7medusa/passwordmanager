#ifndef PASSWORDMANAGER_FIRSTLOGIN_H
#define PASSWORDMANAGER_FIRSTLOGIN_H

#include <QtWidgets>
#include "settings.h"

using namespace std;

class FirstLogin : public QWidget {
    Q_OBJECT
public:
    explicit FirstLogin(QWidget *parent = nullptr);
    signals:
    void firstLoginExited();
private:
    void comparePasswords();
    void writePassword(string password);
    QLineEdit *passwordInputOne, *passwordInputTwo;
    QPushButton *submitButton, *exitButton;
    QLabel *errorText, *passwordInputOneText, *passwordInputTwoText;
};

#endif