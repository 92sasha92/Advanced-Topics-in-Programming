#include "PaperPiece.h"

std::string PaperPiece::toString() {
	return "P" +  this->getPlayerNumber();
}