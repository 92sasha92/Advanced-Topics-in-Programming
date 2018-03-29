#include "ScissorsPiece.h"

std::string ScissorsPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "S";
    } else {
        return "s";
    }
}