#include "decrypt.h"
#include <iomanip>

vector<uint8_t> hexToBytes(const string& hex) {
    vector<uint8_t> bytes;
    if(hex.size() % 2 != 0)
        return bytes;

    bytes.reserve(hex.size() / 2);
    for(size_t i = 0; i < hex.size(); i += 2) {
        unsigned int value = 0;
        std::stringstream ss;
        ss << std::hex << hex.substr(i, 2);
        ss >> value;
        bytes.push_back(static_cast<uint8_t>(value));
    }
    return bytes;
}

string decrypt(const string& encryptedData, AES_ctx ctx, uint8_t iv[16]) {
    vector<uint8_t> buffer = hexToBytes(encryptedData);
    if(buffer.empty() || buffer.size() % AES_BLOCKLEN != 0)
        return "error";

    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_decrypt_buffer(&ctx, buffer.data(), buffer.size());

    if(buffer.empty())
        return "error";

    uint8_t padLen = buffer.back();
    if(padLen == 0 || padLen > AES_BLOCKLEN || padLen > buffer.size())
        return "error";

    for(size_t i = buffer.size() - padLen; i < buffer.size(); ++i) {
        if(buffer[i] != padLen)
            return "error";
    }

    return string(reinterpret_cast<char*>(buffer.data()), buffer.size() - padLen);
}