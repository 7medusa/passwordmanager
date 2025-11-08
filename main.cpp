#include <cstring>
#include <iostream>
#include "outputs.h"
#include "decrypt.h"
#include "encrypt.h"
#include "database.h"
#include <chrono>
#include <openssl/sha.h>
#include "init.h"

const char* dataCSV = "/home/medusa/projekte/passwordmanager/data.csv";
using namespace std;

void keyFromMasterPassword(const char* password, uint8_t* key) {
    uint8_t hash[32];
    SHA256((const uint8_t*)password, strlen(password), hash);
    memcpy(key, hash, 32);//32 bytes for AES-256
}

int function() {
    Csv database(dataCSV);
    while(true) {
        string website;
        string masterPassword;
        switch(decision()) {
            case -1://false input
                break;
            case 1://add login
                break;
            case 2://edit login
                break;
            case 3://delete login
                break;
            case 4://list all logins, but the passwords as *
                break;
            case 5://show login
                break;
            case 6://exit
                return 0;
            default://fatal error
                return -1;
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

    AESCtx ctx{};
    uint8_t key[16];
    uint8_t iv[16];
    generateIvFromTime(iv);
    char* masterPassword = new char[masterPasswordString.length() + 1];
    strcpy(masterPassword, masterPasswordString.c_str());
    keyFromMasterPassword(masterPassword, key);
    delete[] masterPassword;
    AES_init_ctx_iv(&ctx, key, iv);

    //test
    char* testData = "test data";

    string encryptedData = encrypt(testData, ctx);
    cout << "encrypted Data: ";
    for(size_t i = 0; i < encryptedData.size(); i++) {
        cout << hex << setw(2) << setfill('0') << (int)(uint8_t)encryptedData[i];
    }
    cout << endl;

    generateIvFromTime(iv);
    cout << "decrypted Data: " << decrypt(encryptedData, ctx, iv) << endl;
    //test

    return 0;
}