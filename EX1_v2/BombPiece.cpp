#include "BombPiece.h"

BombPiece::BombPiece(int player) :Piece(player), type(PieceFactory::Bomb){
    setCanMove(false);
    strongerThan[PieceFactory::Rock] = Piece::Equal;
    strongerThan[PieceFactory::Paper] = Piece::Equal;
    strongerThan[PieceFactory::Scissors] = Piece::Equal;
    strongerThan[PieceFactory::Bomb] = Piece::Equal;
    strongerThan[PieceFactory::Flag] = Piece::Equal;
}

std::string BombPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "B";
    } else {
        return "b";
    }
}