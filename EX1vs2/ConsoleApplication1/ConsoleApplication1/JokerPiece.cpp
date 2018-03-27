#include "stdafx.h"
#include "JokerPiece.h"

JokerPiece::JokerPiece(int player, PieceFactory::RPSPiecesTypes jokerPiece_) : Piece(player) {
	if (jokerPiece != PieceFactory::Joker || jokerPiece != PieceFactory::Flag || jokerPiece != PieceFactory::Undefined) {
		jokerPiece = jokerPiece_;
	}
	else {
		// TODO: error wrong joker type
	}
}

std::string JokerPiece::toString() {
	return "J" + this->getPlayerNumber() + this->jokerPiece; // TODO: set jokerPiece as char
}