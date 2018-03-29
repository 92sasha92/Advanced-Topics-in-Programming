#include "FlagPiece.h"

FlagPiece::FlagPiece(int player) :Piece(player), type(PieceFactory::Flag){
    setCanMove(false);
    strongerThan[PieceFactory::Rock] = Piece::Weaker;
    strongerThan[PieceFactory::Paper] = Piece::Weaker;
    strongerThan[PieceFactory::Scissors] = Piece::Weaker;
    strongerThan[PieceFactory::Bomb] = Piece::Equal;
    strongerThan[PieceFactory::Flag] = Piece::Equal;
}

std::string FlagPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "F";
    } else {
        return "f";
    }
}