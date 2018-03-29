#include "RockPiece.h"

std::string RockPiece::toString() {
    return "R" + std::to_string(this->getPlayerNumber());
}