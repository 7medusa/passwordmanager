#pragma once
#include <string>
#include <vector>
#include "../libs/tiny-AES-c/aes.hpp"

using namespace std;

bool decryptMasterPassword(const string* masterPassword, const string* masterpasswordPath);

vector<uint8_t> hexToBytes(const string& hex);
string decrypt(const string& encryptedData, AES_ctx ctx, uint8_t iv[16]);