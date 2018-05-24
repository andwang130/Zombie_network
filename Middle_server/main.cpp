#include <iostream>
#include "Msokcet.h"

int main() {
    Csocket ser;
    ser.serever_init("127.0.0.1",8080);
    ser.run();
    return 0;
}