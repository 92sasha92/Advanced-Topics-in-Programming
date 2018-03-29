#pragma once
#include "Piece.h"
#include "PieceFactory.h"

class JokerPiece: public Piece{
  public:
    Piece::RPSPiecesTypes jokerPiece;
    JokerPiece(int player, Piece::RPSPiecesTypes jokerPiece_);
    std::string toString() override;
};