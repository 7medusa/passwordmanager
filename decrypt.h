#pragma once
#include <string>
#include "libs/tiny-AES-c/aes.hpp"

using namespace std;

bool decryptMasterPassword(string masterPassword);

string decrypt(const string& encryptedData, AES_ctx ctx, uint8_t iv[16]);