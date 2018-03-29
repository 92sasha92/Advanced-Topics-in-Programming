#pragma once
#include "Piece.h"

class PieceFactory {
  public:

    static Piece::RPSPiecesTypes charToPieceType(char c);
    static Piece *createPiece(Piece::RPSPiecesTypes cPiece, int player, Piece::RPSPiecesTypes jokerPiece = Piece::Undefined);
};