#include <iostream>
#include "outputs.h"

using namespace std;

int main() {
    while(true) {
        switch(decision()) {
            case -1:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                return 0;
            default:
                return -1;
        }
    }
}