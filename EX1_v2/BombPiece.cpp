#include "BombPiece.h"

BombPiece::BombPiece(int player) :Piece(player) {
    setCanMove(false);
    this->type = Piece::Bomb;
    this->strongerThan[Piece::Rock] = Piece::Equal;
    this->strongerThan[Piece::Paper] = Piece::Equal;
    this->strongerThan[Piece::Scissors] = Piece::Equal;
    this->strongerThan[Piece::Bomb] = Piece::Equal;
    this->strongerThan[Piece::Flag] = Piece::Equal;
}

std::string BombPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "b";
    } else {
        return "B";
    }
}

BombPiece::~BombPiece() {
}