#include "PaperPiece.h"

std::string PaperPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "P";
    } else {
        return "p";
    }
}