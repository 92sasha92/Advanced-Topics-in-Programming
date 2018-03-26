#pragma once
#include "Piece.h"


typedef enum {
	Rock,
	Paper,
	Scissors,
	Bomb,
	Joker,
	Flag,
	Undefined
} RPSPiecesTypes;

RPSPiecesTypes charToPieceType(char c);

Piece *createPiece(RPSPiecesTypes cPiece, int player, RPSPiecesTypes jokerPiece = Undefined);