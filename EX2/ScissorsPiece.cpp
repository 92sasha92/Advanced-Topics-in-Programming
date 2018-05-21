#include "ScissorsPiece.h"

ScissorsPiece::ScissorsPiece(int player) :Piece(player) {
    this->type = Piece::Scissors;
    this->strongerThan[Piece::Rock] = Piece::Weaker;
    this->strongerThan[Piece::Paper] = Piece::Stronger;
    this->strongerThan[Piece::Scissors] = Piece::Equal;
    this->strongerThan[Piece::Bomb] = Piece::Equal;
    this->strongerThan[Piece::Flag] = Piece::Stronger;
}

std::string ScissorsPiece::toString() const {
    if (this->getPlayerNumber() == 2) {
        return "s";
    } else {
        return "S";
    }
}

ScissorsPiece::~ScissorsPiece() {
}