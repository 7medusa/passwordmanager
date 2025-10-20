#include "outputs.h"
#include <iostream>

int decision() {
    cout << "1 for add login\n2to delete login\n3 to list logins\n4 for exit" << endl;
    string s; cin >> s;
    if(s == "1") {
        return 1;
    }
    else if(s == "2") {
        return 2;
    }
    else if(s == "3") {
        return 3;
    }
    else if(s == "4") {
        return 4;
    }
    else {
        cout << "input error" << endl;
        return -1;
    }
}