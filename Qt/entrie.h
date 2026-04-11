#ifndef PASSWORDMANAGER_ENTRIE_H
#define PASSWORDMANAGER_ENTRIE_H

#include <QtWidgets>
#include "../sqlBackend/sql.h"

class Entrie : public QWidget {
    Q_OBJECT
public:
    explicit Entrie(QWidget *parent = nullptr);
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
    QPushButton *closeButton, *saveButton, *showPassword, *deleteButton;
    QLabel *saveText;
    QLineEdit *passwordLine;
    Sql sql;
};

#endif