#ifndef PASSWORDMANAGER_LOGIN_H
#define PASSWORDMANAGER_LOGIN_H

#include <QtWidgets>

using namespace std;

class Login : public QWidget {
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
    string masterpasswordInput;
private:
    QLabel *labelText, *falsePasswordText;
    QPushButton *submitButton, *exitButton, *settingsButton;
    QLineEdit *passwordInput;
    void passwordCheck();
    signals:
    void passwordCorrect();
    void passwordFalse();
};

#endif