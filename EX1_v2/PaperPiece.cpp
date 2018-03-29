#include "PaperPiece.h"

PaperPiece::PaperPiece(int player) :Piece(player), type(PieceFactory::Paper){
    strongerThan[PieceFactory::Rock] = Piece::Stronger;
    strongerThan[PieceFactory::Paper] = Piece::Equal;
    strongerThan[PieceFactory::Scissors] = Piece::Weaker;
    strongerThan[PieceFactory::Bomb] = Piece::Equal;
    strongerThan[PieceFactory::Flag] = Piece::Stronger;
}

std::string PaperPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "P";
    } else {
        return "p";
    }
}