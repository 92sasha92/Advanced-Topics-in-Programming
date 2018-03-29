#pragma once
#include "Piece.h"
#include "PieceFactory.h"

class JokerPiece: public Piece{
  private:
    Piece::RPSPiecesTypes jokerPiece;

  public:
    RPSPiecesTypes getJokerPiece();
    void setJokerPiece(Piece::RPSPiecesTypes NewJpkerPiece);
    JokerPiece(int player, Piece::RPSPiecesTypes jokerPiece_);
    std::string toString() override;
    ~JokerPiece() final;
};