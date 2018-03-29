#include "BombPiece.h"

std::string BombPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "B";
    } else {
        return "b";
    }
}