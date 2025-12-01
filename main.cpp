#include <cstring>
#include <iostream>
#include "decrypt.h"
#include "encrypt.h"
#include "database.h"
#include <chrono>
#include <openssl/sha.h>
#include "init.h"
#include "libs/tiny-AES-c/aes.hpp"
#include <thread>
#include <chrono>

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
    cout << "1 to add login, 2 to edit login, 3 to delete login, 4 to list all logins, 5 to show specific login, 6 to exit" << endl;
    getline(cin, input);
    try {decision = stoi(input);}
    catch(invalid_argument& e) {cout << "input was not an int" << endl;}

    while(true) {
        string website;
        string masterPassword;
        switch(decision) {
            case 1://add login
                break;
            case 2://edit login
                break;
            case 3://delete login
                break;
            case 4://list all logins
                csv.listData();
                break;
            case 5: {
                //show specific login
                string website;
                cout << "Website to show:" << endl;
                getline(cin, website);
                csv.readData(website, ctx);
                break;
            }
            case 6://exit
                exit(0);
                break;
            default:
                cout << "wrong input" << endl;
                break;
        }
    }
}

int main() {
    string masterPasswordString;
    cout << "type your Masterpassword:" << endl;
    //getline(cin, masterPasswordString);
    masterPasswordString = "password";
    if(decryptMasterPassword(masterPasswordString)) {
        cout << "MasterPassword correct" << endl;
    }
    else {
        cerr << "Masterpassword wrong" << endl;
        return -1;
    }

    AES_ctx ctx{};
    uint8_t key[16];
    uint8_t iv[16];
    generateIvFromTime(iv);
    char* masterPassword = new char[masterPasswordString.length() + 1];
    strcpy(masterPassword, masterPasswordString.c_str());
    keyFromMasterPassword(masterPassword, key);
    delete[] masterPassword;
    AES_init_ctx_iv(&ctx, key, iv);

    function(ctx);

    //test
    char* testData = "test data";
    generateIvFromTime(iv);
    string encryptedData = encrypt(testData, ctx, iv);

    //printet die verschlüsselten daten
    cout << "encrypted Data: ";
    for(size_t i = 0; i < encryptedData.size(); i++) {
        cout << hex << setw(2) << setfill('0') << (int)(uint8_t)encryptedData[i];
    }
    cout << endl;
    //cout << endl << "iv:" << iv << endl;;

    //cout << "waiting for 3 seconds" << endl;
    //this_thread::sleep_for(chrono::seconds(5));

    generateIvFromTime(iv);
    cout << "decrypted Data: " << decrypt(encryptedData, ctx, iv) << endl;
    //cout << "iv: " << iv << endl;
    //test

    return 0;
}