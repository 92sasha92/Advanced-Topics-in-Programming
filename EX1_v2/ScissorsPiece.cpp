#include "ScissorsPiece.h"

ScissorsPiece::ScissorsPiece(int player) :Piece(player) {
    this->type = Piece::Scissors;
    this->strongerThan[Piece::Rock] = Piece::Weaker;
    this->strongerThan[Piece::Paper] = Piece::Stronger;
    this->strongerThan[Piece::Scissors] = Piece::Equal;
    this->strongerThan[Piece::Bomb] = Piece::Equal;
    this->strongerThan[Piece::Flag] = Piece::Stronger;
}

std::string ScissorsPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "S";
    } else {
        return "s";
    }
}

ScissorsPiece::~ScissorsPiece() {
}