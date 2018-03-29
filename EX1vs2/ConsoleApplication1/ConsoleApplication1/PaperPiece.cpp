#include "PaperPiece.h"

using namespace std;

std::string PaperPiece::toString() {
	return "P" + this->getPlayerNumber();
}