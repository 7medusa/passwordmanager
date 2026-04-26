#include "passwordgenerator.h"

Passwordgenerator::Passwordgenerator(QWidget *parent) : QWidget(parent) {
    exitButton = new QPushButton("Exit", this);
    generateButton = new QPushButton("Generate", this);
    lengthSlider = new QSlider(Qt::Horizontal, this);
    uppercase = new QCheckBox("Uppercase", this);
    lowercase = new QCheckBox("Lowercase", this);
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

    auto layoutH1 = new QHBoxLayout();
    layoutH1->addWidget(exitButton);
    layoutH1->addWidget(generateButton);

    auto layoutH2 = new QHBoxLayout();
    layoutH2->addWidget(passwordLine);

    auto layoutH3 = new QHBoxLayout();
    layoutH3->addWidget(lengthSlider);
    layoutH3->addWidget(lengthLine);

    auto layoutH4 = new QHBoxLayout();
    layoutH4->addWidget(uppercase);
    layoutH4->addWidget(lowercase);
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