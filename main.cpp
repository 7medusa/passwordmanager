#include <cstring>
#include <iostream>
#include "outputs.h"
#include "decrypt.h"
#include "encrypt.h"
#include "database.h"
#include <chrono>
#include <openssl/sha.h>

const char* dataCSV = "/home/medusa/projekte/passwordmanager/data.csv";
using namespace std;

void keyFromMasterPassword(const char* password, uint8_t* key) {
    uint8_t hash[32];
    SHA256((const uint8_t*)password, strlen(password), hash);
    memcpy(key, hash, 32);//32 bytes for AES-256
}

void generate_iv_from_time(uint8_t* iv) {
    memset(iv, 0, 16);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    memcpy(iv + 8, &ms, sizeof(ms));
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
                database.writeData(false);
                break;
            case 2://edit login
                database.writeData(true);
                break;
            case 3://delete login
                database.deleteData();
                break;
            case 4://list all logins, but the passwords as *
                database.listData();
                break;
            case 5:
                cout << "Website" << endl;
                getline(cin, website);
                cout << "Masterpassword" << endl;
                getline(cin, masterPassword);
                database.readData(website, masterPassword);
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
    return 0;
}