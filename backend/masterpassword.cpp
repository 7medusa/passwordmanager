#include "masterpassword.h"

#include <iostream>
#include <cstring>
#include <chrono>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <fstream>
#include <iomanip>

bool decryptMasterpassword(const string* masterPassword, const string* masterpasswordPath) {
    fstream masterpasswordFile(*masterpasswordPath);
    string hashValue;
    if(masterpasswordFile.is_open())
        getline(masterpasswordFile, hashValue);
    else {
        cerr << "Error: Could not open masterPasswordHashValue file" << endl;
        return false;
    }
    masterpasswordFile.close();
    string masterpasswordInputHashValue = sha256(*masterPassword);
    return masterpasswordInputHashValue == hashValue;
}

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
    for (unsigned int i = 0; i < length; ++i)
        result << hex << setw(2) << setfill('0') << (int)hash[i];
    return result.str();
}

void keyFromMasterpassword(const char* password, uint8_t* key) {
    uint8_t hash[32];
    SHA256((const uint8_t*)password, strlen(password), hash);
    memcpy(key, hash, 32);//32 bytes for AES-256 Bit
}