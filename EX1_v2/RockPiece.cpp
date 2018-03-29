#include "RockPiece.h"

RockPiece::RockPiece(int player) :Piece(player), type(PieceFactory::Rock){
    strongerThan[PieceFactory::Rock] = Piece::Equal;
    strongerThan[PieceFactory::Paper] = Piece::Weaker;
    strongerThan[PieceFactory::Scissors] = Piece::Stronger;
    strongerThan[PieceFactory::Bomb] = Piece::Equal;
    strongerThan[PieceFactory::Flag] = Piece::Stronger;
}

std::string RockPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "R";
    } else {
        return "r";
    }
}