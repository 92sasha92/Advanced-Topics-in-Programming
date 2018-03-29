#include "FlagPiece.h"

std::string FlagPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "F";
    } else {
        return "f";
    }
}