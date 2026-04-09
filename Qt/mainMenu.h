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
    void entrieClicked(int id);
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
    QList<WebsiteEntry> entries;
    Sql sql;
};

class ListItem : public QWidget {
    Q_OBJECT
public:
    explicit ListItem(int id, const QString &text, QWidget *parent = nullptr);
    signals:
        void clicked(int id);
private:
    int entryId;
    void mousePressEvent(QMouseEvent *) override;
};

#endif