#include "firstLogin.h"
#include <fstream>
#include "../backend/masterpassword.h"
#include <iostream>

using namespace std;

FirstLogin::FirstLogin(QWidget *parent) : QWidget(parent) {
    exitButton = new QPushButton("Exit", this);
    submitButton = new QPushButton("Submit", this);
    errorText = new QLabel("", this);
    passwordInputOne = new QLineEdit(this);
    passwordInputTwo = new QLineEdit(this);
    passwordInputOneText = new QLabel("Enter masterpassword:", this);
    passwordInputTwoText = new QLabel("Repeat masterpassword:", this);

    exitButton->setAutoDefault(true);
    submitButton->setAutoDefault(true);

    QObject::connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);
    QObject::connect(submitButton, &QPushButton::clicked, this, &FirstLogin::comparePasswords);
    QObject::connect(passwordInputOne, &QLineEdit::returnPressed, this, [this]() {passwordInputTwo->setFocus();});
    QObject::connect(passwordInputTwo, &QLineEdit::returnPressed, this, [this]() {comparePasswords();});

    auto layoutH1 = new QHBoxLayout();
    layoutH1->addWidget(exitButton);
    layoutH1->addWidget(submitButton);

    auto layout = new QVBoxLayout();
    layout->addLayout(layoutH1);
    layout->addWidget(errorText);
    layout->addWidget(passwordInputOneText);
    layout->addWidget(passwordInputOne);
    layout->addWidget(passwordInputTwoText);
    layout->addWidget(passwordInputTwo);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

void FirstLogin::comparePasswords() {
    string firstPassword = passwordInputOne->text().toStdString();
    string secondPassword = passwordInputTwo->text().toStdString();

    if(firstPassword == secondPassword) {
        writePassword(firstPassword);

        QJsonObject settings;
        settings[QString::fromStdString("firstLogin")] = QString::fromStdString("false");
        QJsonDocument doc(settings);
        QFile settingsFile("settings.json");
        if(settingsFile.open(QIODevice::WriteOnly)) {
            settingsFile.write(doc.toJson());
            settingsFile.close();
        }

        const string masterpasswordPath = "../backend/masterPasswordHashValue";
        ofstream masterpasswordFile(masterpasswordPath);
        if(masterpasswordFile.is_open()) {
            masterpasswordFile << sha256(firstPassword);
            masterpasswordFile.close();
        }

        emit firstLoginExited();
    }
    else {
        errorText->setText(QString::fromStdString("Passwords do not match"));
    }
}

void FirstLogin::writePassword(string password) {}