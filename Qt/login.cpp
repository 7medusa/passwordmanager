#include "login.h"
#include "window.h"
#include "../sqlBackend/masterpassword.h"

Login::Login(QWidget *parent) : QWidget(parent)  {
    labelText = new QLabel("Masterpassword:", this);
    falsePasswordText = new QLabel("", this);
    submitButton = new QPushButton("Submit", this);
    exitButton = new QPushButton("Exit", this);
    passwordInput = new QLineEdit(this);
    settingsButton = new QPushButton("⚙️", this);

    submitButton->setAutoDefault(true);
    exitButton->setAutoDefault(true);
    settingsButton->setAutoDefault(true);

    QObject::connect(submitButton, &QPushButton::clicked, this, &Login::passwordCheck);
    QObject::connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);
    QObject::connect(passwordInput, &QLineEdit::returnPressed, this, &Login::passwordCheck);

    auto layoutH1 = new QHBoxLayout();
    layoutH1->addSpacerItem(new QSpacerItem(400, 200, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layoutH1->addWidget(falsePasswordText);
    layoutH1->addSpacerItem(new QSpacerItem(400, 200, QSizePolicy::Expanding, QSizePolicy::Minimum));

    auto layoutH2 = new QHBoxLayout();
    layoutH2->addSpacerItem(new QSpacerItem(400, 200, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layoutH2->addWidget(labelText);
    layoutH2->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Fixed));
    layoutH2->addWidget(passwordInput);
    layoutH2->addWidget(submitButton);
    layoutH2->addWidget(exitButton);
    layoutH2->addWidget(settingsButton);
    layoutH2->addSpacerItem(new QSpacerItem(400, 200, QSizePolicy::Expanding, QSizePolicy::Minimum));

    auto layout = new QVBoxLayout(this);
    layout->addLayout(layoutH1);
    layout->addLayout(layoutH2);
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);
}

void Login::passwordCheck() {
    masterpasswordInput = passwordInput->text().toStdString();
    if(decryptMasterpassword(&masterpasswordInput, &masterpasswordPath))
        emit passwordCorrect();
    else
        falsePasswordText->setText("Wrong password");
}