#include "stdafx.h"
#include "Piece.h"

Piece::Piece(int player) : playerNumber(player) {
	std::cout << "sdsdsd";
}

int Piece::getPlayerNumber() {
	return this->playerNumber;
}

std::string Piece::toString()
{
	return "base class";
}

Piece::~Piece()
{
}
