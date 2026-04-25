#include "settings.h"


Settings::Settings(QWidget *parent) : QWidget(parent) {
    dark = false;

    exitButton = new QPushButton("Exit", this);
    saveButton = new QPushButton("Save", this);
    changeMasterpassword = new QPushButton("Change masterpassword", this);
    if(dark)
        darkModeButton = new QPushButton("Darkmode", this);
    else
        darkModeButton = new QPushButton("Lightmode", this);
    darkModeLabel = new QLabel("Darkmode: ", this);

    QObject::connect(exitButton, &QPushButton::clicked, this, [this]() {emit settingsExited();});
    QObject::connect(darkModeButton, &QPushButton::clicked, this, &Settings::toogleDarkMode);

    auto layoutH1 = new QHBoxLayout();
    layoutH1->addWidget(exitButton);
    //layoutH1->addWidget(saveButton);

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

void Settings::saveSettings(string dataType, string data) {
    settings[QString::fromStdString(dataType)] = QString::fromStdString(data);
    QJsonDocument doc(settings);
    QFile settingsFile("settings.json");
    if(settingsFile.open(QIODevice::WriteOnly)) {
        settingsFile.write(doc.toJson());
        settingsFile.close();
    }
}

void Settings::loadSettings() {
    QFile settingsFile("settings.json");
    if(settingsFile.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(settingsFile.readAll());
        if (!doc.isNull()) {
            settings = doc.object();
        }
        settingsFile.close();
    }
    if(settings["theme"].toString() == "dark") {
        dark = true;
        darkModeButton->setText("Darkmode");
    }
    else {
        dark = false;
        darkModeButton->setText("Lightmode");
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
        saveSettings("theme", "dark");
    else
        saveSettings("theme", "light");
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
