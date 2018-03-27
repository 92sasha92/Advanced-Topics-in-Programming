#pragma once
#include "Piece.h"

class PaperPiece: public Piece{
public:
	PaperPiece(int player):Piece(player) {}
	void toString() override;
};