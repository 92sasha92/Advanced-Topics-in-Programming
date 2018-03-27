#pragma once
#include "Piece.h"
#include "PieceFactory.h"

class JokerPiece: public Piece{
public:
	PieceFactory::RPSPiecesTypes jokerPiece;
	JokerPiece(int player, PieceFactory::RPSPiecesTypes jokerPiece_);
	std::string toString() override;
};