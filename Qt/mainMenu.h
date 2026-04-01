#ifndef PASSWORDMANAGER_MAINMENU_H
#define PASSWORDMANAGER_MAINMENU_H

#include <QtWidgets>

using namespace std;

class MainMenu : public QWidget {
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
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