#include "encrypt.h"
#include <cstring>
#include <iostream>
#include <chrono>
#include <openssl/evp.h>
#include <openssl/sha.h>

string sha256(const string &input) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_sha256();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length = 0;

    EVP_DigestInit_ex(ctx, md, nullptr);
    EVP_DigestUpdate(ctx, input.data(), input.size());
    EVP_DigestFinal_ex(ctx, hash, &length);
    EVP_MD_CTX_free(ctx);

    std::ostringstream result;
    for (unsigned int i = 0; i < length; ++i) {
        result << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return result.str();
}

void keyFromMasterPassword(const char* password, uint8_t* key) {
    uint8_t hash[32];
    SHA256((const uint8_t*)password, strlen(password), hash);
    memcpy(key, hash, 32);//32 bytes for AES-256 Bit
}

string bytesToHex(const uint8_t* data, size_t len) {
    ostringstream out;
    for(size_t i = 0; i < len; ++i)
        out << hex << setw(2) << setfill('0') << static_cast<int>(data[i]);
    return out.str();
}

string encrypt(const char* data, AES_ctx ctx, uint8_t iv[16]) {
    const size_t length = strlen(data);
    vector<uint8_t> buffer(data, data + length);
    pkcs7Pad(buffer);

    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_encrypt_buffer(&ctx, buffer.data(), buffer.size());

    return bytesToHex(buffer.data(), buffer.size());
}

void pkcs7Pad(vector<uint8_t>& buffer) {
    const size_t padLen = AES_BLOCKLEN - (buffer.size() % AES_BLOCKLEN);
    buffer.insert(buffer.end(), padLen, static_cast<uint8_t>(padLen));
}