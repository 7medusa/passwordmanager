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
    void readData(string website, AES_ctx ctx);
    void writeData(bool edit);
    void deleteData();
private:
    string filename;
    ofstream fileOutput;
    ifstream fileInput;
};