#include <iostream>
#include "outputs.h"
#include "decrypt.h"
#include "encrypt.h"
#include "database.h"

#define data "/home/medusa/projekte/passwordmanager/data.csv"

using namespace std;

int main() {
    Csv database(data);
    while(true) {
        switch(decision()) {
            case -1://false input
                break;
            case 1://add login
                database.writeData(false);
                break;
            case 2://edit login
                database.writeData(true);
                break;
            case 3://delete login
                database.deleteData();
                break;
            case 4://list all logins, but the passwords as *
                database.listData();
                break;
            case 5://exit
                return 0;
            default://fatal error
                return -1;
        }
    }
}