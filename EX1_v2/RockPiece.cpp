#include "RockPiece.h"

std::string RockPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "R";
    } else {
        return "r";
    }
}