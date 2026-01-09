#include <cstring>
#include <iostream>
#include "decrypt.h"
#include "encrypt.h"
#include "database.h"
#include <openssl/sha.h>
#include "init.h"
#include "libs/tiny-AES-c/aes.hpp"

using namespace std;

const char* dataCSV = "/home/medusa/projekte/passwordmanager/data.csv";
const string masterpasswordPath = "../masterPasswordHashValue";
Csv csv(dataCSV);

bool createMasterpassword() {
    fstream masterpasswordFile(masterpasswordPath);
    if(!masterpasswordFile.is_open()) {
        masterpasswordFile.close();
        string firstMasterpassword;
        string secondMasterpassword;
        cout << "set your masterpassword" << endl;
        getline(cin, firstMasterpassword);
        cout << "repeat your masterpassword" << endl;
        getline(cin, secondMasterpassword);
        if(firstMasterpassword == secondMasterpassword) {
            masterpasswordFile << sha256(firstMasterpassword);
            masterpasswordFile.close();
            return true;
        }
        else {cout << "password do not match" << endl;return false;}
    }
    else {
        string currentHashValue;
        getline(masterpasswordFile, currentHashValue);
        if(currentHashValue.empty()) {
            string firstMasterpassword;
            string secondMasterpassword;
            cout << "set your masterpassword" << endl;
            getline(cin, firstMasterpassword);
            cout << "repeat your masterpassword" << endl;
            getline(cin, secondMasterpassword);
            if(firstMasterpassword == secondMasterpassword) {
                masterpasswordFile << sha256(firstMasterpassword);
                masterpasswordFile.close();
                return true;
            }
            else {cout << "password do not match" << endl;return false;}
        }
        else {return true;}
    }
}

void changeMasterpassword(AES_ctx ctx) {
    string oldMasterpassword;
    string newMasterpassword;
    string tempNewMasterpassword;
    string hashValueOldMasterpassword;
    cout << "enter your old masterpassword" << endl;
    getline(cin, oldMasterpassword);
    if(!decryptMasterPassword(&oldMasterpassword, &masterpasswordPath)) {
        cout << "MasterPassword incorrect" << endl;
        return;
    }

    cout << "enter your new masterpassword" << endl;
    getline(cin, newMasterpassword);
    cout << "enter your new masterpassword again" << endl;
    getline(cin, tempNewMasterpassword);
    if(tempNewMasterpassword != newMasterpassword) {
        cout << "password do not match" << endl;
        return;
    }

    csv.recryptData(ctx, oldMasterpassword, newMasterpassword);
    ofstream masterPasswordFile(masterpasswordPath);
    masterPasswordFile << sha256(newMasterpassword);
    masterPasswordFile.close();
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
                if(agreement == "y" || agreement == "Y") {csv.deleteData(&website);}
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
            case 6://edit masterpassword
                changeMasterpassword(ctx);
                break;
            case 7://exit
                exit(0);
            default:
                cout << "wrong input" << endl;
                break;
        }
    }
}

int main() {
    //check if there is a masterpassword
    bool loop = true;
    while(loop) {
        if(createMasterpassword()) {
            loop = false;
        }
    }

    string masterPasswordString;
    cout << "type your Masterpassword:" << endl;
    getline(cin, masterPasswordString);
    if(decryptMasterPassword(&masterPasswordString, &masterpasswordPath)) {
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