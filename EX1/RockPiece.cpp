#include "RockPiece.h"

std::string RockPiece::toString() {
	return "R" + this->getPlayerNumber();
}