#include "passwordgenerator.h"
#include <string>

using namespace std;

Passwordgenerator::Passwordgenerator(QWidget *parent) : QWidget(parent) {
    exitButton = new QPushButton("Exit", this);
    generateButton = new QPushButton("Generate", this);
    copyButton = new QPushButton("Copy", this);
    lengthSlider = new QSlider(Qt::Horizontal, this);
    uppercase = new QCheckBox("Uppercase", this);
    numbers = new QCheckBox("Numbers", this);
    symbols = new QCheckBox("Symbols", this);
    passwordLine = new QLineEdit(this);
    lengthLine = new QLineEdit(this);

    passwordLine->setReadOnly(true);
    lengthSlider->setRange(0, 99);
    lengthSlider->setValue(10);
    lengthSlider->setTickPosition(QSlider::TicksBelow);
    lengthSlider->setTickInterval(1);
    lengthLine->setMaxLength(2);

    QObject::connect(exitButton, &QPushButton::clicked, this, [this]() {emit passwordgeneratorExited();});
    QObject::connect(lengthSlider, &QSlider::valueChanged, this, &Passwordgenerator::updateLengthLine);
    QObject::connect(lengthLine, &QLineEdit::textEdited, this, &Passwordgenerator::updateLengthSlider);
    QObject::connect(generateButton, &QPushButton::clicked, this, &Passwordgenerator::generatePassword);
    QObject::connect(copyButton, &QPushButton::clicked, this, &Passwordgenerator::copyPassword);


    auto layoutH1 = new QHBoxLayout();
    layoutH1->addWidget(exitButton);
    layoutH1->addWidget(copyButton);
    layoutH1->addWidget(generateButton);

    auto layoutH2 = new QHBoxLayout();
    layoutH2->addWidget(passwordLine);

    auto layoutH3 = new QHBoxLayout();
    layoutH3->addWidget(lengthSlider);
    layoutH3->addWidget(lengthLine);

    auto layoutH4 = new QHBoxLayout();
    layoutH4->addWidget(uppercase);
    layoutH4->addWidget(numbers);
    layoutH4->addWidget(symbols);

    auto layout = new QVBoxLayout();
    layout->addLayout(layoutH1);
    layout->addLayout(layoutH2);
    layout->addLayout(layoutH3);
    layout->addLayout(layoutH4);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
    
    updateLengthLine();
}

void Passwordgenerator::updateLengthSlider() {
    lengthSlider->setValue(lengthLine->text().toInt());
}

void Passwordgenerator::updateLengthLine() {
    lengthLine->setText(QString::number(lengthSlider->value()));
}

void Passwordgenerator::generatePassword() {
    size_t length = lengthSlider->value();
    const string lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
    const string uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string numberChars = "0123456789";
    const string symbolChars = "!@#$%^&*()-_=+[]{}<>?/";
    string charset = lowercaseChars;
    if(uppercase->isChecked())
        charset += uppercaseChars;
    if(numbers->isChecked())
        charset += numberChars;
    if(symbols->isChecked())
        charset += symbolChars;
    if(charset.empty())
        return;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<std::size_t> dist(0, charset.size() - 1);

    string password;
    password.reserve(length);

    for(size_t i = 0; i < length; ++i) {
        password += charset[dist(gen)];
    }

    passwordLine->setText(QString::fromStdString(password));
}

void Passwordgenerator::copyPassword() {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(passwordLine->text());
}