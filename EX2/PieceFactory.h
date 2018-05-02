#pragma once
#include "Piece.h"
#include <memory>

class PieceFactory {
  public:

    static Piece::RPSPiecesTypes charToPieceType(char c);
//    static Piece *createPiece(Piece::RPSPiecesTypes cPiece, int player, Piece::RPSPiecesTypes jokerPiece = Piece::Undefined);
    static std::unique_ptr<Piece> createPiece(Piece::RPSPiecesTypes pieceType, int player, Piece::RPSPiecesTypes jokerPiece = Piece::Undefined);
};