#include <iostream>
#include "RPS.h"

int main(int argc, char *argv[]) {
    RPS rps;
    rps.Parser(0);
    rps.Parser(1);
    rps.PrintBoard();
    return 0;
}

