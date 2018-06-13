#include <iostream>
#include "Msokcet.h"

int main() {
    Csocket ser;
    ser.serever_init("0.0.0.0", 8080);
    ser.run();
    return 0;
}