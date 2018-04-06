#include "JokerPiece.h"

JokerPiece::JokerPiece(int player, Piece::RPSPiecesTypes jokerPiece_): Piece(player), jokerPiece(Piece::Undefined) {
    this->type = Piece::Joker;
    if (jokerPiece_ != Piece::Joker && jokerPiece_ != Piece::Flag && jokerPiece_!= Piece::Undefined) {
        jokerPiece = jokerPiece_;
    } else {
        jokerPiece = Piece::Undefined;
        std::cout << "ERROR: unsuported joker type" << std::endl;
    }
}

std::string JokerPiece::toString() {
    if (this->getPlayerNumber() == 1) {
        return "j" + std::to_string(this->jokerPiece); // TODO: set jokerPiece as char
    } else {
        return "J" + std::to_string(this->jokerPiece); // TODO: set jokerPiece as char
    }
}

Piece::RPSPiecesTypes JokerPiece::getJokerPiece() {
    return this->jokerPiece;
}

void JokerPiece::setJokerPiece(Piece::RPSPiecesTypes NewJpkerPiece) {
    this->jokerPiece = NewJpkerPiece;
}


JokerPiece::~JokerPiece() {
}