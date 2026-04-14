#include "mainMenu.h"
#include <fstream>
#include <iostream>
#include "../defines.h"

using namespace std;

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    exitButton = new QPushButton("Exit", this);
    addButton = new QPushButton("Add", this);
    searchLabel = new QLabel("search:", this);
    entrieLabel = new QLabel("Entries: " + QString::number(-1), this);
    search = new QLineEdit(this);
    list = new QScrollArea(this);
    listItem = new QWidget(this);
    listLayout = new QVBoxLayout(listItem);

    exitButton->setAutoDefault(true);
    addButton->setAutoDefault(true);
    list->setWidgetResizable(true);
    list->setWidget(listItem);

    QObject::connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);
    QObject::connect(search, &QLineEdit::textEdited, this, [this]() {searchEntrie(search->text().toStdString());});

    auto layoutH1 = new QHBoxLayout();
    layoutH1->addWidget(exitButton);
    layoutH1->addWidget(addButton);

    auto layoutH2 = new QHBoxLayout();
    layoutH2->addWidget(searchLabel);layoutH2->addWidget(search);

    auto layoutV1 = new QVBoxLayout();
    layoutV1->addWidget(entrieLabel);
    layoutV1->addWidget(list);

    auto layout = new QVBoxLayout();
    layout->addLayout(layoutH1);
    layout->addLayout(layoutH2);
    layout->addLayout(layoutV1);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);

    addEntrie();
}

void MainMenu::refreshList() {
    while(QLayoutItem *item = listLayout->takeAt(0)) {
        if(item->widget())
            item->widget()->deleteLater();
        delete item;
    }
    for(const WebsiteEntry &entry : entries) {
        auto *item = new ListItem(entry.id, entry.website);
        listLayout->addWidget(item);
        connect(item, &ListItem::clicked, this, [this](int id) {
            emit entrieClicked(id);
#ifdef DEBUG
            cout << "clicked: " << id << endl;
#endif
        });
    }
    listLayout->addStretch();
}

void MainMenu::addEntrie() {
    sql.openDb();
    sql.readTable();
    sql.closeDb();
    entries.clear();
    for(const WebsiteDataName& data : sql.tableEntries) {
        WebsiteEntry entry;
        entry.id = data.id;
        entry.website = QString::fromStdString(data.website);
        entries.append(entry);
    }
    entries.removeFirst();
    refreshList();
    n = entries.size();
    entrieLabel->setText("Entries: " + QString::number(n));
}

void MainMenu::entrieRemoved() {
    entries.clear();
    addEntrie();
}

void MainMenu::searchEntrie(string entrieName) {
    sql.openDb();
    sql.readTable();
    sql.closeDb();
    entries.clear();
    for(const WebsiteDataName& data : sql.tableEntries) {
        if(entrieName.empty()) {
            addEntrie();
            return;
        }
        else if(data.website.starts_with(entrieName)) {
            WebsiteEntry entry;
            entry.id = data.id;
            entry.website = QString::fromStdString(data.website);
            entries.append(entry);
        }
    }
    refreshList();
    n = entries.size();
    entrieLabel->setText("Entries: " + QString::number(n));
}

ListItem::ListItem(int id, const QString &text, QWidget *parent) : QWidget(parent), entryId(id) {  // ID speichern
    QLabel *label = new QLabel(text, this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    setLayout(layout);
    setMouseTracking(true);
}

void ListItem::mousePressEvent(QMouseEvent *) {
    emit clicked(entryId);
}