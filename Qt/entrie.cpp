#include "entrie.h"
#include <iostream>
#include "../defines.h"

using namespace std;

Entrie::Entrie(AES_ctx &ctx, QWidget *parent) : QWidget(parent), ctx(ctx) {
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

    QObject::connect(closeButton, &QPushButton::clicked, this, &Entrie::exited);
    QObject::connect(deleteButton, &QPushButton::clicked, this, &Entrie::deleteEntrie);
    QObject::connect(showPassword, &QPushButton::clicked, this, [this, ctx]() { showPasswordClicked(ctx); });

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

void Entrie::showPasswordClicked(AES_ctx ctx) {
    if(passwordShown) {
        passwordLine->setText("********");
        passwordShown = false;
        sql.websiteData.password = "";
    }
    else {
        sql.openDb();
        sql.readData(id, ctx);
        sql.closeDb();
        passwordLine->setText(QString::fromStdString(sql.websiteData.password));
        passwordShown = false;
    }
}

void Entrie::encryptPassword() {}

void Entrie::decryptPassword() {}

AddEntrie::AddEntrie(QWidget *parent) : QWidget(parent) {
    addButton = new QPushButton("add", this);
    exitButton = new QPushButton("exit", this);
    websiteLine = new QLineEdit(this);
    usernameLine = new QLineEdit(this);
    passwordLine = new QLineEdit(this);
    websiteLabel = new QLabel("Website:", this);
    usernameLabel = new QLabel("Username:", this);
    passwordLabel = new QLabel("Password:", this);

    addButton->setAutoDefault(true);
    exitButton->setAutoDefault(true);
}

void AddEntrie::encryptPassword() {}