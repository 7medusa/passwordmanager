#pragma once
#include <string>

using namespace std;

//entschlüsseln

string sha256(const string &input);

string decrypt(bool masterPassword, string encryptedData);

bool decryptMasterPassword(string masterPassword);