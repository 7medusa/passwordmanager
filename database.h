#pragma once
#include <string>

using namespace std;

class Csv {
public:
    Csv(string fileName);
    ~Csv();
    void listData();
    void writeData(bool edit);
    void readData();
    void deleteData();
private:
    const string filename;
};