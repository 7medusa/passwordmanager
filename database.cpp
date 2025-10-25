#include "database.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "decrypt.h"

Csv::Csv(string filename) {
    this->filename = filename;
}

Csv::~Csv() {
    fileInput.close();
    fileOutput.close();
}

void Csv::listData() {//list all login entrys
    fileInput.open(filename);
    const int labelWidth = 10;
    while(fileInput.good()) {
        string line;
        string column1, column2, column3, column4;
        istringstream ss(line);
        getline(fileInput, column1, ',');
        getline(fileInput, column2, ',');
        getline(fileInput, column3, ',');
        getline(fileInput, column4, ',');
        if(column2.empty()) {
            break;
        }
        Login login{stoi(column1), column2, column3, column4};
        string censordPassword = "********";
        cout << "----------------------------------\n";
        cout << left << setw(labelWidth) << "ID:" << login.id << '\n';//debug
        cout << left << setw(labelWidth) << "Website:" << login.website << '\n';
        cout << left << setw(labelWidth) << "Username:" << login.username << '\n';
        cout << left << setw(labelWidth) << "Password:" << censordPassword << '\n';
    }
    cout << "----------------------------------\n";
    fileInput.close();
}

void Csv::readData(string website, string masterPassword) {
    fileInput.open(filename);
    while(fileInput.good()) {
        const int labelWidth = 10;
        string line;
        string column1, column2, column3, column4;
        istringstream ss(line);
        getline(fileInput, column1, ',');
        getline(fileInput, column2, ',');
        getline(fileInput, column3, ',');
        getline(fileInput, column4, ',');
        if(column2 == website) {
            Login login{stoi(column1), column2, column3, column4};
            cout << "----------------------------------\n";
            cout << left << setw(labelWidth) << "ID:" << login.id << '\n';//debug
            cout << left << setw(labelWidth) << "Website:" << login.website << '\n';
            cout << left << setw(labelWidth) << "Username:" << login.username << '\n';
            cout << left << setw(labelWidth) << "Password:" << decrypt(decryptMasterPassword(masterPassword), login.password) << '\n';
            cout << "----------------------------------\n";
            fileInput.close();
            return;
        }
    }
    cout << "----------------------------------\n";
    cout << "No login found for website " << website << '\n';
    cout << "----------------------------------\n";
    fileInput.close();
}

void Csv::writeData(bool edit) {}

void Csv::deleteData() {}