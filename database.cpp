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
    while(fileInput.good()) {
        constexpr int labelWidth = 10;
        string line;
        string column1, column2, column3, column4;
        istringstream ss(line);
        getline(fileInput, column1, ',');
        getline(fileInput, column2, ',');
        getline(fileInput, column3, ',');
        getline(fileInput, column4, ',');
        if(column2.empty() || column2 == "p%#%p") {
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

void Csv::readData(string* website, AES_ctx ctx) {
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
        if(column2 == *website) {
            constexpr int labelWidth = 10;
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

void Csv::writeData(AES_ctx ctx, string* website, string* username, string password) {
    rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));
    fileInput.open(filename);

    int lineNumber = -1;//because line 0 are infos
    bool newLine = false;
    while(fileInput.good()) {
        lineNumber++;
        string line;
        string column2;
        istringstream ss(line);
        getline(fileInput, column2, ',');
        if(column2 == "p%#%p") {
            newLine = false;
            fileInput.close();
            break;
        }
        else if(column2.empty()) {
            newLine = true;
            fileInput.close();
            break;
        }
    }
    uint8_t iv[16];
    generateIvFromTime(iv);
    string encryptedPassword = encrypt(&password[0], ctx, iv);
    doc.SetCell(newLine, 2, *website);
    doc.SetCell(newLine, 3, *username);
    doc.SetCell(newLine, 4, encryptedPassword);
    doc.SetCell(newLine, 5, iv);
    if(newLine) {
        doc.SetCell(newLine, 0, lineNumber+1);
    }
    fileInput.close();
    doc.Save(filename);
}

void Csv::editData(int change, AES_ctx ctx, string* website, string changeValue="") {
    rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));
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
        if(column2 == *website) {
            if(change > 0 && change < 4) {
                if(change == 3) {//change password and generate iv
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

void Csv::deleteData(string* website) {
    fileInput.open(filename);
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
        if(column2 == *website) {
            for(int i = 0; i < 6; i++) {
                doc.SetCell(column1, i, "");
            }
            doc.SetCell(column1, 2, "p%#%p");
            doc.Save(filename);
        }
        fileInput.close();
    }
}

void Csv::recryptData(AES_ctx ctx, const string& oldPasswordString, const string& newPasswordString) {
    fileInput.open(filename);
    rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));
    int n = 0;
    while(fileInput.good()) {
        n++;
        string line;
        string column1, column2, column3, column4, column5;
        istringstream ss(line);
        getline(fileInput, column1, ',');
        getline(fileInput, column2, ',');
        getline(fileInput, column3, ',');
        getline(fileInput, column4, ',');
        getline(fileInput, column5, ',');
        if(column2 != "p%#%p") {
            const string& hashPassword = column4;

            string oldIv = column5;
            uint8_t oldKey[32];
            char* oldPassword = new char[oldPasswordString.length() + 1];
            keyFromMasterPassword(oldPassword, oldKey);
            AES_init_ctx_iv(&ctx, oldKey, reinterpret_cast<uint8_t *>(oldIv.data()));
            string decryptedPassword = decrypt(hashPassword, ctx, reinterpret_cast<uint8_t *>(oldIv.data()));

            uint8_t newIv[16];
            uint8_t newKey[32];
            generateIvFromTime(newIv);
            char* newPassword = new char[newPasswordString.length() + 1];
            keyFromMasterPassword(newPassword, newKey);
            AES_init_ctx_iv(&ctx, newKey, newIv);
            string encryptedPassword = encrypt(decryptedPassword.c_str(), ctx, newIv);

            doc.SetCell(n, 4, encryptedPassword);
            doc.SetCell(n, 5, newIv);
            doc.Save(filename);
        }
        else {
            fileInput.close();
            return;
        }
    }
    fileInput.close();
}
