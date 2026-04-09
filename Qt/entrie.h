#ifndef PASSWORDMANAGER_ENTRIE_H
#define PASSWORDMANAGER_ENTRIE_H

#include <QtWidgets>
#include "../sqlBackend/sql.h"

class Entrie : public QWidget {
    Q_OBJECT
public:
    explicit Entrie(QWidget *parent = nullptr);
    int id;
    QLabel *idText;
    signals:
    void exited();
private:
    QPushButton *closeButton, *saveButton, *showPassword, *deleteButton;
    QLabel *saveText;
    QLineEdit *website, *username, *password;
    Sql sql;
};

#endif