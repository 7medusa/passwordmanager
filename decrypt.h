#pragma once
#include <string>
#include "libs/tiny-AES-c/aes.hpp"

using namespace std;

//entschlüsseln

string sha256(const string &input);

string decrypt(bool masterPassword, string encryptedData);

bool decryptMasterPassword(string masterPassword);