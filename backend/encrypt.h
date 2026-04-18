#ifndef PASSWORDMANAGER_ENCRYPT_H
#define PASSWORDMANAGER_ENCRYPT_H

#include <string>
#include <vector>
#include "../libs/tiny-AES-c/aes.hpp"

using namespace std;

string encrypt(const char* data, AES_ctx ctx, uint8_t iv[16]);
string bytesToHex(const uint8_t* data, size_t len);
void pkcs7Pad(vector<uint8_t>& buffer);
void generateIvFromTime(uint8_t* iv);
void keyFromMasterPassword(const char* password, uint8_t* key);

#endif