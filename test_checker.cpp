#include "checker.hpp"

int main() {
    CheckerFunction testA(25, 70, 0.7);
    CheckerFunction testB(50, 85, 0);
    
    assert(batteryIsOk(testA) == true);
    assert(batteryIsOk(testB) == false);

    return 0;
}