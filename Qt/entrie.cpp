#include "entrie.h"
#include <iostream>
#include "../defines.h"

using namespace std;

Entrie::Entrie(QWidget *parent) : QWidget(parent) {
    passwordShown = false;

    closeButton = new QPushButton("Close", this);
    saveButton = new QPushButton("Save", this);
    showPassword = new QPushButton("Show password", this);
    deleteButton = new QPushButton("Delete", this);
    saveText = new QLabel("", this);
    idText = new QLabel("", this);
    websiteLine = new QLineEdit(this);
    usernameLine = new QLineEdit(this);
    passwordLine = new QLineEdit("********", this);

    closeButton->setAutoDefault(true);
    saveButton->setAutoDefault(true);
    deleteButton->setAutoDefault(true);
    showPassword->setAutoDefault(true);
    deleteButton->setAutoDefault(true);

    QObject::connect(closeButton, &QPushButton::clicked, this, &Entrie::exited);
    QObject::connect(deleteButton, &QPushButton::clicked, this, &Entrie::deleteEntrie);

    auto layoutH1 = new QHBoxLayout();
    layoutH1->addWidget(saveButton);
    layoutH1->addWidget(closeButton);
    layoutH1->addWidget(deleteButton);

    auto layoutH2 = new QHBoxLayout();
    layoutH2->addWidget(passwordLine);
    layoutH2->addWidget(showPassword);

    auto layout = new QVBoxLayout(this);
    layout->addLayout(layoutH1);
#ifdef DEBUG
    layout->addWidget(idText);
#endif
    layout->addWidget(websiteLine);
    layout->addWidget(usernameLine);
    layout->addLayout(layoutH2);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

void Entrie::updateEntrie() {}

void Entrie::deleteEntrie() {
    sql.openDb();
    sql.deleteData(id);
    sql.closeDb();
    emit exited();
}

void Entrie::showPasswordClicked() {}

void Entrie::encryptPassword() {}

void Entrie::decryptPassword() {}