#include "JokerPiece.h"

JokerPiece::JokerPiece(int player, PieceFactory::RPSPiecesTypes jokerPiece_): Piece(player) {
	if (jokerPiece != PieceFactory::Joker || jokerPiece != PieceFactory::Flag || jokerPiece != PieceFactory::Undefined) {
		jokerPiece = jokerPiece_;
	} else {
		// TODO: error wrong joker type
	}
}

void JokerPiece::toString() {
	std::cout << "R" << this->getPlayerNumber();
}