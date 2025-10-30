#pragma once
#include <string>
#include <fstream>

using namespace std;

struct Login {
    int id;
    string website;
    string username;
    string password;
};

class Csv {
public:
    Csv(const char* fileName);
    ~Csv();
    void listData();
    void readData(string website, string maserPassword);
    void writeData(bool edit);
    void deleteData();
private:
    string filename;
    ofstream fileOutput;
    ifstream fileInput;
};