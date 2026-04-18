#ifndef PASSWORDMANAGER_MAINMENU_H
#define PASSWORDMANAGER_MAINMENU_H

#include <QtWidgets>
#include "../backend/sql.h"

using namespace std;

struct WebsiteEntry {
    int id;
    QString website;
};

class MainMenu : public QWidget {
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
    void addEntrie();
    void entrieUpdate();
    QLineEdit *search;
    signals:
    void entrieClicked(int id);
    void addEntrieClicked();
private:
    void refreshList();
    void searchEntrie(string entrieName);
    int n;
    QPushButton *exitButton, *addButton, *clearFilterButton;
    QLabel *searchLabel, *entrieLabel;
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