#ifndef PASSWORDMANAGER_LOGIN_H
#define PASSWORDMANAGER_LOGIN_H

#include <QtWidgets>

class Login : public QWidget {
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
protected:
    QLabel *passwordText;
    QPushButton *submitButton, *exitButton;
    QLineEdit *passwordInput;
    QToolButton *settingsButton;
    void passwordCheck();
    signals:
    void passwordCorrect();
};

#endif