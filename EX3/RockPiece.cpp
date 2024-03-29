#include "RockPiece.h"

RockPiece::RockPiece(int player) :Piece(player) {
    this->type = Piece::Rock;
    this->strongerThan[Piece::Rock] = Piece::Equal;
    this->strongerThan[Piece::Paper] = Piece::Weaker;
    this->strongerThan[Piece::Scissors] = Piece::Stronger;
    this->strongerThan[Piece::Bomb] = Piece::Equal;
    this->strongerThan[Piece::Flag] = Piece::Stronger;
}

std::string RockPiece::toString() const {
    if (this->getPlayerNumber() == 2) {
        return "r";
    } else {
        return "R";
    }
}

RockPiece::~RockPiece() {
}