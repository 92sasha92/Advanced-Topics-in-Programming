#include "PaperPiece.h"

std::string PaperPiece::toString() {
    return "P" +  std::to_string(this->getPlayerNumber());
}