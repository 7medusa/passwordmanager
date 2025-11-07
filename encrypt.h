#pragma once
#include <string>
#include "libs/tiny-AES-c/aes.hpp"

using namespace std;

string sha256(const string &input);

string encrypt(char* data, AESCtx ctx);