#pragma once
#include <string>
#include "libs/tiny-AES-c/aes.hpp"

using namespace std;

bool decryptMasterPassword(const string* masterPassword, const string* masterpasswordPath);

string decrypt(const string& encryptedData, AES_ctx ctx, uint8_t iv[16]);