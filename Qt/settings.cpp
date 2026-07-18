#include "settings.h"


Settings::Settings(QWidget *parent) : QWidget(parent) {
    dark = false;
    firstLogin = true;

    exitButton = new QPushButton("Exit", this);
    changeMasterpassword = new QPushButton("Change masterpassword(not working)", this);
    if(dark)
        darkModeButton = new QPushButton("Darkmode", this);
    else
        darkModeButton = new QPushButton("Lightmode", this);
    darkModeLabel = new QLabel("Color: ", this);

    QObject::connect(exitButton, &QPushButton::clicked, this, [this]() {emit settingsExited();});
    QObject::connect(darkModeButton, &QPushButton::clicked, this, &Settings::toogleDarkMode);

    auto layoutH1 = new QHBoxLayout();
    layoutH1->addWidget(exitButton);

    auto layoutH2 = new QHBoxLayout();
    layoutH2->addWidget(darkModeLabel);
    layoutH2->addWidget(darkModeButton);

    auto layoutH3 = new QHBoxLayout();
    layoutH3->addWidget(changeMasterpassword);

    auto layout = new QVBoxLayout();
    layout->addLayout(layoutH1);
    layout->addLayout(layoutH2);
    layout->addLayout(layoutH3);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

void Settings::saveSettings(string dataType, bool data) {
    QSaveFile settingsFile("settings.json");
    QJsonObject settings;

    {
        QFile readFile("settings.json");
        if (readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonDocument loadDoc = QJsonDocument::fromJson(readFile.readAll());
            readFile.close();
            if (loadDoc.isObject())
                settings = loadDoc.object();
        }
    }

    settings[QString::fromStdString(dataType)] = QJsonValue::fromVariant(data);

    QJsonDocument doc(settings);

    if (settingsFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        settingsFile.write(doc.toJson(QJsonDocument::Indented));
        settingsFile.commit();
    }
}

void Settings::loadSettings() {
    QFile settingsFile("settings.json");
    QJsonObject settings;
    QJsonDocument doc(settings);

    if(settingsFile.open(QIODevice::ReadOnly)) {
        QJsonDocument loadDoc = QJsonDocument::fromJson(settingsFile.readAll());
        settingsFile.close();
        if(loadDoc.isObject())
            settings = loadDoc.object();
    }

    firstLogin = settings.value("firstLogin").toBool();
    dark = settings.value("dark").toBool();
    if(dark) {
        darkModeButton->setText("Darkmode");
        darkMode();
    }
    else {
        darkModeButton->setText("Lightmode");
        lightMode();
    }
    QJsonDocument saveDoc(settings);
    if(settingsFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        settingsFile.write(saveDoc.toJson());
        settingsFile.close();
    }
}

void Settings::toogleDarkMode() {
    if(!dark) {
        darkMode();
        darkModeButton->setText("Darkmode");
    }
    else {
        lightMode();
        darkModeButton->setText("Lightmode");
    }
    dark = !dark;
    if(dark)
        saveSettings("dark", true);
    else
        saveSettings("dark", false);
}

void Settings::darkMode() {
    qApp->setStyle("Fusion");
    palette.setColor(QPalette::Window, QColor(53, 53, 53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(25, 25, 25));
    palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53, 53, 53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, QColor(42, 130, 218));
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    palette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(palette);
}

void Settings::lightMode() {
    palette = qApp->style()->standardPalette();
    qApp->setPalette(palette);
}
