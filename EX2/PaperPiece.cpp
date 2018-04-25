#include "PaperPiece.h"

PaperPiece::PaperPiece(int player) :Piece(player) {
    this->type = Piece::Paper;
    this->strongerThan[Piece::Rock] = Piece::Stronger;
    this->strongerThan[Piece::Paper] = Piece::Equal;
    this->strongerThan[Piece::Scissors] = Piece::Weaker;
    this->strongerThan[Piece::Bomb] = Piece::Equal;
    this->strongerThan[Piece::Flag] = Piece::Stronger;
}

std::string PaperPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "p";
    } else {
        return "P";
    }
}

PaperPiece::~PaperPiece() {
}