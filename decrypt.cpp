#include "decrypt.h"
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <iomanip>
#include <chrono>
#include <cstring>
#include "encrypt.h"

bool decryptMasterPassword(const string* masterPassword, const string* masterpasswordPath) {
    fstream masterPasswordFile(*masterpasswordPath);
    string hashValue;
    if(masterPasswordFile.is_open()) {
        getline(masterPasswordFile, hashValue);
    }
    else {
        cerr << "Error: Could not open masterPasswordHashValue file" << endl;
        return false;
    }
    masterPasswordFile.close();
    string masterPasswordInputHashValue = sha256(*masterPassword);
    if(masterPasswordInputHashValue == hashValue) {
        return true;
    }
    return false;
}

string decrypt(const string& encryptedData, AES_ctx ctx, uint8_t iv[16]) {
    uint8_t buffer[32] = {};
    constexpr size_t bufferLength = 32;
    memcpy(buffer, encryptedData.data(), min(encryptedData.size(), bufferLength));

    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_decrypt_buffer(&ctx, buffer, bufferLength);

    return (char*)buffer;
}