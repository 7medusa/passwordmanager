#include "encrypt.h"
#include <sstream>
#include <iomanip>
#include <cstring>
#include <chrono>
#include <openssl/sha.h>

string encrypt(const char* data, AES_ctx ctx, uint8_t iv[16]) {
    const size_t length = strlen(data);
    vector<uint8_t> buffer(data, data + length);
    pkcs7Pad(buffer);

    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_encrypt_buffer(&ctx, buffer.data(), buffer.size());

    return bytesToHex(buffer.data(), buffer.size());
}

string bytesToHex(const uint8_t* data, size_t len) {
    ostringstream out;
    for(size_t i = 0; i < len; ++i)
        out << hex << setw(2) << setfill('0') << static_cast<int>(data[i]);
    return out.str();
}

void pkcs7Pad(vector<uint8_t>& buffer) {
    const size_t padLen = AES_BLOCKLEN - (buffer.size() % AES_BLOCKLEN);
    buffer.insert(buffer.end(), padLen, static_cast<uint8_t>(padLen));
}

void generateIvFromTime(uint8_t* iv) {
    memset(iv, 0, 16);
    auto ms = chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    memcpy(iv + 8, &ms, sizeof(ms));
}

void keyFromMasterPassword(const char* password, uint8_t* key) {
    uint8_t hash[32];
    SHA256((const uint8_t*)password, strlen(password), hash);
    memcpy(key, hash, 32);//32 bytes for AES-256 Bit
}