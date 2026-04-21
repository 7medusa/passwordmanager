#include "entrie.h"
#include <iostream>
#include "../defines.h"

using namespace std;

Entrie::Entrie(AES_ctx &ctx, QWidget *parent) : QWidget(parent), ctx(ctx) {
    passwordShown = false;

    closeButton = new QPushButton("Close", this);
    copyButton = new QPushButton("Copy", this);
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
    QObject::connect(showPassword, &QPushButton::clicked, this, &Entrie::showPasswordClicked);
    QObject::connect(copyButton, &QPushButton::clicked, this, [this]() {QApplication::clipboard()->setText(QString::fromStdString(sql.websiteData.password));});
    QObject::connect(saveButton, &QPushButton::clicked, this, &Entrie::updateEntrie);

    auto layoutH1 = new QHBoxLayout();
    layoutH1->addWidget(saveButton);
    layoutH1->addWidget(closeButton);
    layoutH1->addWidget(deleteButton);

    auto layoutH2 = new QHBoxLayout();
    layoutH2->addWidget(passwordLine);
    layoutH2->addWidget(showPassword);
    layoutH2->addWidget(copyButton);

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

void Entrie::updateEntrie() {
    sql.openDb();
    if(websiteLine->text().toStdString() !=sql.websiteData.website)
        sql.updateData("website", id, websiteLine->text().toStdString(), ctx);
    if(usernameLine->text().toStdString() !=sql.websiteData.username)
        sql.updateData("username", id, usernameLine->text().toStdString(), ctx);
    if(passwordLine->text().toStdString() != "********") {
        if(passwordLine->text().toStdString() !=sql.websiteData.password)
            sql.updateData("password", id, passwordLine->text().toStdString(), ctx);
    }
    sql.closeDb();
}

void Entrie::deleteEntrie() {
    sql.openDb();
    sql.deleteData(id);
    sql.closeDb();
    emit exited();
}

void Entrie::showPasswordClicked() {
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
        passwordShown = true;
    }
}

AddEntrie::AddEntrie(AES_ctx &ctx, QWidget *parent) : QWidget(parent), ctx(ctx) {
    exitButton = new QPushButton("exit without save", this);
    addButton = new QPushButton("save", this);
    websiteLabel = new QLabel("Website:", this);
    usernameLabel = new QLabel("Username:", this);
    passwordLabel = new QLabel("Password:", this);
    websiteLine = new QLineEdit(this);
    usernameLine = new QLineEdit(this);
    passwordLine = new QLineEdit(this);

    exitButton->setAutoDefault(true);
    addButton->setAutoDefault(true);

    QObject::connect(exitButton, &QPushButton::clicked, this, [this](){emit addEntrieExited();});
    QObject::connect(addButton, &QPushButton::clicked, this, &AddEntrie::saveEntrie);

    auto layoutH1 = new QHBoxLayout();
    layoutH1->addWidget(exitButton);
    layoutH1->addWidget(addButton);

    auto layoutH2 = new QHBoxLayout();
    layoutH2->addWidget(websiteLabel);
    layoutH2->addWidget(websiteLine);

    auto layoutH3 = new QHBoxLayout();
    layoutH3->addWidget(usernameLabel);
    layoutH3->addWidget(usernameLine);

    auto layoutH4 = new QHBoxLayout();
    layoutH4->addWidget(passwordLabel);
    layoutH4->addWidget(passwordLine);

    auto layout = new QVBoxLayout();
    layout->addLayout(layoutH1);
    layout->addLayout(layoutH2);
    layout->addLayout(layoutH3);
    layout->addLayout(layoutH4);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

void AddEntrie::saveEntrie() {
    string website = websiteLine->text().toStdString();
    string username = usernameLine->text().toStdString();
    string password = passwordLine->text().toStdString();
    sql.openDb();
    sql.insertData(website, username, password, ctx);
    sql.closeDb();
    emit addEntrieExited();
}