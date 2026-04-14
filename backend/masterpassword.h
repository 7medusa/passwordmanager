#ifndef PASSWORDMANAGER_MASTERPASSWORD_H
#define PASSWORDMANAGER_MASTERPASSWORD_H

#include <cstdint>
#include <string>

using namespace std;

const string masterpasswordPath = "../sqlBackend/masterPasswordHashValue";

bool decryptMasterpassword(const string* masterPassword, const string* masterpasswordPath);
string sha256(const string &input);
void keyFromMasterpassword(const char* password, uint8_t* key);

#endif