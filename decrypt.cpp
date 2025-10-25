#include "decrypt.h"
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>

string sha256(const string &input) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_sha256();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length = 0;

    EVP_DigestInit_ex(ctx, md, nullptr);
    EVP_DigestUpdate(ctx, input.data(), input.size());
    EVP_DigestFinal_ex(ctx, hash, &length);
    EVP_MD_CTX_free(ctx);

    std::ostringstream result;
    for (unsigned int i = 0; i < length; ++i) {
        result << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return result.str();
}

string decrypt(bool masterPassword, string encryptedData) {
    return encryptedData;
}

bool decryptMasterPassword(string masterPassword) {
    ifstream masterPasswordFile("../masterPasswordHashValue");
    string hashValue;
    if(masterPasswordFile.is_open()) {
        getline(masterPasswordFile, hashValue);
    }
    else {
        cerr << "Error: Could not open masterPasswordHashValue file" << endl;
        return false;
    }
    masterPasswordFile.close();
    string masterPasswordInputHashValue = sha256(masterPassword);
    if(masterPasswordInputHashValue == hashValue) {
        return true;
    }
    else {
        return false;
    }
}