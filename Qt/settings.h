#ifndef PASSWORDMANAGER_SETTINGS_H
#define PASSWORDMANAGER_SETTINGS_H

#include <QtWidgets>
#include "../backend/sql.h"

class Settings : public QWidget {
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = nullptr);
    void loadSettings();
    void darkMode();
    void lightMode();
    bool dark;
    signals:
    void settingsExited();
private:
    void saveSettings(string dataType, string data);
    void toogleDarkMode();
    QJsonObject settings;
    QString settingsPath;
    QPalette palette;
    QPushButton *exitButton, *darkModeButton, *changeMasterpassword;
    QLabel *darkModeLabel;
    Sql sql;
};

#endif