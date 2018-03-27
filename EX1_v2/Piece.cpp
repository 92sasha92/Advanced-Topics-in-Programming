#include "Piece.h"

Piece::Piece(int player) : playerNumber(player) {
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
