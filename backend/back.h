#pragma once

#include <iostream>
#include <cstring>
#include "../libs/tiny-AES-c/aes.hpp"

using namespace std;

inline const char* dataCSV = "/home/medusa/projekte/passwordmanager/backend/data.csv";
const string masterpasswordPath = "/home/medusa/projekte/passwordmanager/backend/masterPasswordHashValue";
bool createMasterpassword();
void changeMasterpassword(AES_ctx ctx);
void function(AES_ctx ctx);
int back();