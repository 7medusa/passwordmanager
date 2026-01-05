#pragma once
#include <string>
#include <fstream>
#include "libs/tiny-AES-c/aes.hpp"

using namespace std;

class AESCtx;

struct Login {
    int id;
    string website;
    string username;
    string password;
    string iv;
};

class Csv {
public:
    Csv(const char* fileName);
    ~Csv();
    void listData();
    void readData(string* website, AES_ctx ctx);
    void writeData(AES_ctx ctx, string* website, string* username, string password);
    void editData(int change, AES_ctx ctx, string* website, string changeValue);
    void deleteData(string* website);
private:
    string filename;
    ofstream fileOutput;
    ifstream fileInput;
};