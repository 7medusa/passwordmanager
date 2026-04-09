#ifndef PASSWORDMANAGER_MAINMENU_H
#define PASSWORDMANAGER_MAINMENU_H

#include <QtWidgets>
#include "../sqlBackend/sql.h"

using namespace std;

struct WebsiteEntry {
    int id;
    QString website;
};

class MainMenu : public QWidget {
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
    signals:
    void entrieClicked(const QString &itemText);
private:
    void addEntry();
    void removeEntry();
    void refreshList();
    QPushButton *exitButton, *addButton;
    QLabel *label;
    QLineEdit *search;
    QScrollArea *list;
    QWidget *listItem;
    QVBoxLayout *listLayout;
    QStringList entries;
    Sql sql;
};

class ListItem : public QWidget {
    Q_OBJECT
public:
    explicit ListItem(const QString &text, QWidget *parent = nullptr);
    signals:
        void clicked(const QString &itemText);
private:
    void mousePressEvent(QMouseEvent *) override;
};

#endif