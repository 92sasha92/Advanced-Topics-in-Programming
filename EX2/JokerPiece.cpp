#include "JokerPiece.h"

JokerPiece::JokerPiece(int player, Piece::RPSPiecesTypes jokerPiece_): Piece(player), jokerPiece(Piece::Undefined) {
    this->type = Piece::Joker;
    if (jokerPiece_ != Piece::Joker && jokerPiece_ != Piece::Flag && jokerPiece_!= Piece::Undefined) {
        jokerPiece = jokerPiece_;
    } else {
        jokerPiece = Piece::Undefined;
        std::cout << "ERROR: unsupported joker type" << std::endl;
    }
}

std::string JokerPiece::toString() {
    if (this->getPlayerNumber() == 2) {
        return "j";
    } else {
        return "J";
    }
}

int JokerPiece::getCanMove() {
	if (this->jokerPiece == Piece::Bomb) {
		return 0;
	} else {
		return 1;
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