#ifndef PASSWORDMANAGER_ENTRIE_H
#define PASSWORDMANAGER_ENTRIE_H

#include <QtWidgets>
#include "../backend/sql.h"

class Entrie : public QWidget {
    Q_OBJECT
public:
    explicit Entrie(AES_ctx &ctx, QWidget *parent = nullptr);
    int id;
    string website, username;
    QLabel *idText;
    QLineEdit *websiteLine, *usernameLine;
    signals:
    void exited();
private:
    void updateEntrie();
    void deleteEntrie();
    void showPasswordClicked();
    void encryptPassword();
    void decryptPassword();
    bool passwordShown;
    AES_ctx& ctx;
    QPushButton *closeButton, *saveButton, *showPassword, *deleteButton;
    QLabel *saveText;
    QLineEdit *passwordLine;
    Sql sql;
};

class AddEntrie : public QWidget {
    Q_OBJECT
public:
    explicit AddEntrie(AES_ctx &ctx, QWidget *parent = nullptr);
    signals:
    void addEntrieExited();
private:
    void saveEntrie();
    QPushButton *exitButton, *addButton;
    QLabel *websiteLabel, *usernameLabel, *passwordLabel;
    QLineEdit *websiteLine, *usernameLine, *passwordLine;
    Sql sql;
    AES_ctx& ctx;
};

#endif