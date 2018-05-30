#include "FlagPiece.h"

FlagPiece::FlagPiece(int player) :Piece(player) {
    setCanMove(false);
    this->type = Piece::Flag;
    this->strongerThan[Piece::Rock] = Piece::Weaker;
    this->strongerThan[Piece::Paper] = Piece::Weaker;
    this->strongerThan[Piece::Scissors] = Piece::Weaker;
    this->strongerThan[Piece::Bomb] = Piece::Equal;
    this->strongerThan[Piece::Flag] = Piece::Equal;
}

std::string FlagPiece::toString() const {
    if (this->getPlayerNumber() == 2) {
        return "f";
    } else {
        return "F";
    }
}

FlagPiece::~FlagPiece() {
}