#include "login.h"
#include "window.h"

Login::Login(QWidget *parent) : QWidget(parent)  {
    passwordText = new QLabel(this);
    submitButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    passwordInput = new QLineEdit(this);
    settingsButton = new QToolButton(this);

    passwordText->setText("Masterpassword:");
    submitButton->setText("Submit");
    exitButton->setText("Exit");
    settingsButton->setText("⚙️");

    QObject::connect(submitButton, &QPushButton::clicked, this, &Login::passwordCheck);
    QObject::connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(passwordText);
    layout->addWidget(passwordInput);
    layout->addWidget(submitButton);
    layout->addWidget(exitButton);
    layout->addWidget(settingsButton);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

void Login::passwordCheck() {
    emit passwordCorrect();
}