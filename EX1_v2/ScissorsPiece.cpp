#include "ScissorsPiece.h"

std::string ScissorsPiece::toString() {
    return "S" + std::to_string(this->getPlayerNumber());
}