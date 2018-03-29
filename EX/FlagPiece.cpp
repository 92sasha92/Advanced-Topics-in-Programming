#include "FlagPiece.h"

std::string FlagPiece::toString() {
    return "F" + std::to_string(this->getPlayerNumber());
}