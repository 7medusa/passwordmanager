#include <cstring>
#include <iostream>
#include "decrypt.h"
#include "encrypt.h"
#include "database.h"
#include <chrono>
#include <openssl/sha.h>
#include "init.h"
#include "libs/tiny-AES-c/aes.hpp"

using namespace std;

const char* dataCSV = "/home/medusa/projekte/passwordmanager/data.csv";
Csv csv(dataCSV);

void keyFromMasterPassword(const char* password, uint8_t* key) {
    uint8_t hash[32];
    SHA256((const uint8_t*)password, strlen(password), hash);
    memcpy(key, hash, 32);//32 bytes for AES-256 Bit
}

void function(AES_ctx ctx) {
    string input;
    int decision = -1;
    cout << "1 to add login, 2 to edit login, 3 to delete login, 4 to list all logins, 5 to show specific login, 6 to edit masterpassword, 7 to exit:" << endl;
    getline(cin, input);
    try {decision = stoi(input);}
    catch(invalid_argument& e) {cout << "error: " << endl;}

    while(true) {
        switch(decision) {
            case 1: {
                //add login
                string website;
                string username;
                string password;
                cout << "website:" << endl;
                getline(cin, website);
                cout << "username:" << endl;
                getline(cin, username);
                cout << "password:" << endl;
                getline(cin, password);
                csv.writeData(ctx, &website, &username, password);
                break;
            }
            case 2: {//edit login
                string website;
                string changeString;
                cout << "enter the website to edit:" << endl;
                getline(cin, website);
                cout << "attribute to change\n1 for website name, 2 for username, 3 for password" << endl;
                getline(cin, changeString);
                try {
                    int change = stoi(changeString);
                    string changeValue;
                    cout << "change value:" << endl;
                    getline(cin, changeValue);
                    csv.editData(change, ctx, &website, changeValue);
                }
                catch(invalid_argument& e) {cout << "input was not an int" << endl;}
                break;
            }
            case 3: {//delete login
                string website;
                string agreement;
                cout << "website to delete:" << endl;
                getline(cin, website);
                cout << "you sure? [y/n]" << endl;
                getline(cin, agreement);
                if(agreement == "y" || agreement == "Y") {csv.deleteData(website);}
                else {cout << "aborted" << endl;}
                break;
            }
            case 4://list all logins
                csv.listData();
                break;
            case 5: {//show specific login
                string website;
                cout << "website to show:" << endl;
                getline(cin, website);
                csv.readData(&website, ctx);
                break;
            }
            case 6: {//edit masterpassword
                //important warning
                cout << "if you change your masterpassword all encrypted passwords will be gone, do you want to continiue\n[y/n]" << endl;
                getline(cin, input);
                if(input == "y") {
                    string newMasterPassword;
                    cout << "new masterpassword:" << endl;
                    getline(cin, newMasterPassword);
                    string hashValue = sha256(newMasterPassword);
                    ofstream masterPasswordFile("../masterPasswordHashValue");
                    masterPasswordFile << hashValue;
                    masterPasswordFile.close();
                    cout << "masterpassword changed" << endl;
                }
                else {cout << "aborted" << endl;}
            }
            case 7://exit
                exit(0);
            default:
                cout << "wrong input" << endl;
                break;
        }
    }
}

int main() {
    string masterPasswordString;
    cout << "type your Masterpassword:" << endl;
    getline(cin, masterPasswordString);
    if(decryptMasterPassword(masterPasswordString)) {
        cout << "MasterPassword correct" << endl;
    }
    else {
        cerr << "Masterpassword wrong" << endl;
        return -1;
    }

    AES_ctx ctx{};
    uint8_t key[32];
    uint8_t iv[16];
    generateIvFromTime(iv);
    char* masterPassword = new char[masterPasswordString.length() + 1];
    strcpy(masterPassword, masterPasswordString.c_str());
    keyFromMasterPassword(masterPassword, key);
    delete[] masterPassword;
    AES_init_ctx_iv(&ctx, key, iv);

    function(ctx);

    return 0;
}

//for later:
/*
if(masterPasswordFile.is_open()) {
        getline(masterPasswordFile, hashValue);
    }
*/
//to do list:
//set masterpassword for first time