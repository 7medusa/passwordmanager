#ifndef PASSWORDMANAGER_DECRYPT_H
#define PASSWORDMANAGER_DECRYPT_H

#include <string>
#include <vector>
#include "../libs/tiny-AES-c/aes.hpp"

using namespace std;

vector<uint8_t> hexToBytes(const string& hex);
string decrypt(const string& encryptedData, AES_ctx ctx, uint8_t iv[16]);

#endif