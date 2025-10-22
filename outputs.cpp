#include "outputs.h"
#include <iostream>

int decision() {
    cout << "1 for add login\n2 to edit login\n3 to delete login\n4 to list logins\n5 to show login\n6 for exit" << endl;
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
    else if(s == "5") {
        return 5;
    }
    else if(s == "6") {
        return 6;
    }
    else {
        cout << "input error" << endl;
        return -1;
    }
}