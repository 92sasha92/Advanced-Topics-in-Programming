#include "Piece.h"

Piece::Piece(int player) : type(Undefined), playerNumber(player), canMove(true) {
}

int Piece::getPlayerNumber() {
    return this->playerNumber;
}

int Piece::getCanMove()
{
	return this->canMove;
}

void Piece::setCanMove(bool isMovable)
{
	this->canMove = isMovable;
}

std::string Piece::toString()
{
    return "base class";
}


Piece::~Piece()
{
}
