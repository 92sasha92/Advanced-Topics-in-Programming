#include "BombPiece.h"

std::string BombPiece::toString() {
    return "B" + std::to_string(this->getPlayerNumber());
}