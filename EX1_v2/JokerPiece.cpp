#include "JokerPiece.h"

JokerPiece::JokerPiece(int player, PieceFactory::RPSPiecesTypes jokerPiece_): Piece(player), jokerPiece(PieceFactory::Undefined) {
    if (jokerPiece_ != PieceFactory::Joker && jokerPiece_ != PieceFactory::Flag && jokerPiece_!= PieceFactory::Undefined) {
        jokerPiece = jokerPiece_;
    } else {
        jokerPiece = PieceFactory::Undefined;
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