#include "stdafx.h"
#include "BombPiece.h"

std::string BombPiece::toString() {
	return "B" + this->getPlayerNumber();
}


