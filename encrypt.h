#pragma once
#include <string>
#include "libs/tiny-AES-c/aes.hpp"

using namespace std;

string sha256(const string &input);

void keyFromMasterPassword(const char* password, uint8_t* key);

string encrypt(const char* data, AES_ctx ctx, uint8_t iv[16]);