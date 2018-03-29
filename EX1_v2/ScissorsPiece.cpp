#include "ScissorsPiece.h"

ScissorsPiece::ScissorsPiece(int player) :Piece(player), type(PieceFactory::Scissors){
    strongerThan[PieceFactory::Rock] = Piece::Weaker;
    strongerThan[PieceFactory::Paper] = Piece::Stronger;
    strongerThan[PieceFactory::Scissors] = Piece::Equal;
    strongerThan[PieceFactory::Bomb] = Piece::Equal;
    strongerThan[PieceFactory::Flag] = Piece::Stronger;
}

std::string ScissorsPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "S";
    } else {
        return "s";
    }
}