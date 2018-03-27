#include "JokerPiece.h"

JokerPiece::JokerPiece(int player, PieceFactory::RPSPiecesTypes jokerPiece_): Piece(player), jokerPiece(PieceFactory::Undefined) {
    if (jokerPiece_ != PieceFactory::Joker && jokerPiece_ != PieceFactory::Flag && jokerPiece_!= PieceFactory::Undefined) {
        jokerPiece = jokerPiece_;
    } else {
        jokerPiece = PieceFactory::Undefined;
        std::cout << "ERROR: unsuported joke type" << std::endl;
        // TODO: error wrong joker type
    }
}

std::string JokerPiece::toString() {
    return "J" + std::to_string(this->getPlayerNumber()) + std::to_string(this->jokerPiece); // TODO: set jokerPiece as char
}