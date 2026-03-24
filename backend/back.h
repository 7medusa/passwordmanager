#pragma once

#include "../libs/tiny-AES-c/aes.hpp"

bool createMasterpassword();
void changeMasterpassword(AES_ctx ctx);
void function(AES_ctx ctx);
int back();