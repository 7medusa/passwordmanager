#include "entrie.h"
#include <iostream>
#include "../defines.h"

using namespace std;

Entrie::Entrie(QWidget *parent) : QWidget(parent) {
    closeButton = new QPushButton("Close", this);
    saveButton = new QPushButton("Save", this);
    showPassword = new QPushButton("Show password", this);
    deleteButton = new QPushButton("Delete", this);
    saveText = new QLabel("", this);
    idText = new QLabel("", this);
    website = new QLineEdit(this);
    username = new QLineEdit(this);
    password = new QLineEdit(this);

    closeButton->setAutoDefault(true);
    saveButton->setAutoDefault(true);
    deleteButton->setAutoDefault(true);
    showPassword->setAutoDefault(true);
    deleteButton->setAutoDefault(true);

    QObject::connect(closeButton, &QPushButton::clicked, this, &Entrie::exited);

    auto layoutH1 = new QVBoxLayout();
    layoutH1->addWidget(saveButton);
    layoutH1->addWidget(closeButton);
    layoutH1->addWidget(deleteButton);

    auto layoutH2 = new QVBoxLayout();
    layoutH2->addWidget(password);
    layoutH2->addWidget(showPassword);

    auto layout = new QVBoxLayout(this);
    layout->addLayout(layoutH1);
#ifdef DEBUG
    layout->addWidget(idText);
#endif
    layout->addWidget(website);
    layout->addWidget(username);
    layout->addLayout(layoutH2);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}