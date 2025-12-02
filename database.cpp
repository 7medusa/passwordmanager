#include "database.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "decrypt.h"
#include "encrypt.h"
#include "init.h"
#include "libs/rapidcsv/src/rapidcsv.h"

Csv::Csv(const char* filename) {
    this->filename = filename;
}

Csv::~Csv() {
    fileInput.close();
    fileOutput.close();
}

void Csv::listData() {
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
        cout << "----------------------------------\n";
        cout << left << setw(labelWidth) << "ID:" << login.id << '\n';
        cout << left << setw(labelWidth) << "Website:" << login.website << '\n';
        cout << left << setw(labelWidth) << "Username:" << login.username << '\n';
        cout << left << setw(labelWidth) << "Password:" << "********" << '\n';
    }
    cout << "----------------------------------\n";
    fileInput.close();
}

void Csv::readData(string website, AES_ctx ctx) {
    fileInput.open(filename);
    while(fileInput.good()) {
        const int labelWidth = 10;
        string line;
        string column1, column2, column3, column4, column5;
        istringstream ss(line);
        getline(fileInput, column1, ',');
        getline(fileInput, column2, ',');
        getline(fileInput, column3, ',');
        getline(fileInput, column4, ',');
        getline(fileInput, column5, ',');
        if(column2 == website) {
            Login login{stoi(column1), column2, column3, column4, column5};
            cout << "----------------------------------\n";
            cout << left << setw(labelWidth) << "ID:" << login.id << '\n';
            cout << left << setw(labelWidth) << "Website:" << login.website << '\n';
            cout << left << setw(labelWidth) << "Username:" << login.username << '\n';
            cout << left << setw(labelWidth) << "Password:" << decrypt(login.password, ctx, reinterpret_cast<uint8_t *>(login.iv.data())) << '\n';
            cout << left << setw(labelWidth) << "IV:" << login.iv << '\n';
            cout << "----------------------------------\n";
            fileInput.close();
            return;
        }
    }
    cout << "----------------------------------\n";
    cout << "No login found for website: " << website << '\n';
    cout << "----------------------------------\n";
    fileInput.close();
}

void Csv::writeData(bool edit, int change, AES_ctx ctx, string website="", string changeValue="") {
    rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));
    if(edit) {
        fileInput.open(filename);
        while(fileInput.good()) {
            string line;
            string column1, column2, column3, column4, column5;
            istringstream ss(line);
            getline(fileInput, column1, ',');
            getline(fileInput, column2, ',');
            getline(fileInput, column3, ',');
            getline(fileInput, column4, ',');
            getline(fileInput, column5, ',');
            if(column2 == website) {
                if(change < 1 || change > 4) {
                    if(change == 4) {//change password and generate iv
                        uint8_t iv[16];
                        generateIvFromTime(iv);
                        string password = encrypt(&changeValue[0], ctx, iv);
                        doc.SetCell(column1, 3, password);
                        doc.SetCell(column1, 4, iv);
                    }
                    else {
                        doc.SetCell(column1, change + 1, changeValue);
                    }
                    doc.Save(filename);
                }
                else {
                    cerr << "fatal error" << endl;
                }
            }
            fileInput.close();
        }
    }
    else {
        //write new login and check for an empty spot in the csv, if isnt one avaible go to the end of the csv
    }
}

void Csv::deleteData(string website) {
    rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));
    while(fileInput.good()) {
        string line;
        string column1, column2, column3, column4, column5;
        istringstream ss(line);
        getline(fileInput, column1, ',');
        getline(fileInput, column2, ',');
        getline(fileInput, column3, ',');
        getline(fileInput, column4, ',');
        getline(fileInput, column5, ',');
        if(column2 == website) {
            for(int i = 0; i < 6; i++) {
                doc.SetCell(column1, i, "");
            }
            doc.Save(filename);
        }
    }
}

//to do list:
//write new login
//write all input calls from the user