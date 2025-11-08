#pragma once
#include <string>
#include "libs/tiny-AES-c/aes.hpp"

using namespace std;

bool decryptMasterPassword(string masterPassword);

string decrypt(string encryptedData, AESCtx ctx, uint8_t iv[16]);