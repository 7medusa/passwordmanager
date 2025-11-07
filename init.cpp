#include "init.h"
#include <chrono>
#include <cstring>

void generateIvFromTime(uint8_t* iv) {
    memset(iv, 0, 16);
    auto ms = chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    memcpy(iv + 8, &ms, sizeof(ms));
}
