#include "JokerPiece.h"

JokerPiece::JokerPiece(int player, Piece::RPSPiecesTypes jokerPiece_): Piece(player), jokerPiece(Piece::Undefined) {
    this->type = Piece::Joker;
    if (jokerPiece_ != Piece::Joker && jokerPiece_ != Piece::Flag && jokerPiece_!= Piece::Undefined) {
        jokerPiece = jokerPiece_;
    } else {
        jokerPiece = Piece::Undefined;
        std::cout << "ERROR: unsuported joker type" << std::endl;
        // TODO: error wrong joker type
    }
}

std::string JokerPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "J" +std::to_string(this->jokerPiece); // TODO: set jokerPiece as char
    } else {
        return "j" + std::to_string(this->jokerPiece); // TODO: set jokerPiece as char
    }
}