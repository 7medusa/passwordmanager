#ifndef PASSWORDMANAGER_PASSWORDGENERATOR_H
#define PASSWORDMANAGER_PASSWORDGENERATOR_H

#include <QtWidgets>

class Passwordgenerator : public QWidget {
    Q_OBJECT
public:
    explicit Passwordgenerator(QWidget *parent = nullptr);
    signals:
    void passwordgeneratorExited();
private:
    void updateLengthSlider();
    void updateLengthLine();
    void generatePassword();
    QLineEdit *passwordLine, *lengthLine;
    QPushButton *exitButton, *generateButton;
    QCheckBox *uppercase, *lowercase, *numbers, *symbols;
    QString password;
    QSlider *lengthSlider;
    bool uppercaseChecked, lowercaseChecked, numbersChecked, symbolsChecked;
};

#endif