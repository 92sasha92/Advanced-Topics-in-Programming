#include "FlagPiece.h"

std::string FlagPiece::toString() {
	return "F" + this->getPlayerNumber();
}
