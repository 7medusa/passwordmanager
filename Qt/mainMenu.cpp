#include "mainMenu.h"
#include <fstream>

using namespace std;

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    exitButton = new QPushButton("Exit", this);
    addButton = new QPushButton("Add", this);
    label = new QLabel("search:", this);
    search = new QLineEdit(this);
    list = new QScrollArea(this);
    listItem = new QWidget(this);
    listLayout = new QVBoxLayout(listItem);

    exitButton->setAutoDefault(true);//enter triggers the button
    addButton->setAutoDefault(true);
    list->setWidgetResizable(true);
    list->setWidget(listItem);

    QObject::connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);

    auto layoutH1 = new QVBoxLayout();
    layoutH1->addWidget(exitButton);
    layoutH1->addWidget(addButton);
    layoutH1->addWidget(label);
    layoutH1->addWidget(search);
    layoutH1->addWidget(list);

    auto layout = new QVBoxLayout();
    layout->addLayout(layoutH1);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);

    addEntry();
    refreshList();
}

ListItem::ListItem(const QString &text, QWidget *parent) : QWidget(parent){
    QLabel *label = new QLabel(text, this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    setLayout(layout);
    setMouseTracking(true);
}

void ListItem::mousePressEvent(QMouseEvent *) {
    emit clicked(this->findChild<QLabel *>()->text());
}

void MainMenu::refreshList() {
    while(QLayoutItem *item = listLayout->takeAt(0)) {
        if(item->widget())
            item->widget()->deleteLater();
        delete item;
    }
    for(const QString &entry : entries) {
        auto *item = new ListItem(entry);
        listLayout->addWidget(item);
        connect(item, &ListItem::clicked, this, [](const QString &text) {
            qDebug() << "Clicked:" << text;
        });
    }
    listLayout->addStretch();
}

void MainMenu::addEntry() {
    ifstream fileInput;
    fileInput.open("/home/medusa/projekte/passwordmanager/backend/data.csv");
    string line;
    while(getline(fileInput, line)) {
        string column1, column2, column3, column4, column5;
        istringstream ss(line);
        getline(ss, column1, ',');
        getline(ss, column2, ',');
        getline(ss, column3, ',');
        getline(ss, column4, ',');
        getline(ss, column5);
        entries.append(QString::fromStdString(column2));
    }
    refreshList();
}

void MainMenu::removeEntry() {
    entries.clear();
    addEntry();
}