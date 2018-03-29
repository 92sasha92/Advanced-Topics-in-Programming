#pragma once
#include "Piece.h"

class PaperPiece: public Piece{
  public:
    PaperPiece(int player);
    std::string toString() override;
};