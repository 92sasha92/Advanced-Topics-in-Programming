#include "RockPiece.h"

RockPiece::RockPiece(int player) :Piece(player) {
    this->type = Piece::Rock;
    this->strongerThan[Piece::Rock] = Piece::Equal;
    this->strongerThan[Piece::Paper] = Piece::Weaker;
    this->strongerThan[Piece::Scissors] = Piece::Stronger;
    this->strongerThan[Piece::Bomb] = Piece::Equal;
    this->strongerThan[Piece::Flag] = Piece::Stronger;
}

std::string RockPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "R";
    } else {
        return "r";
    }
}