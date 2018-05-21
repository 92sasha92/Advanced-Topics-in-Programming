#pragma once

#include "Piece.h"
#include "PiecePosition.h"
#include "MyPoint.h"

class MyPiecePosition: public PiecePosition {
private:
    Piece::RPSPiecesTypes type;
    MyPoint position;
    Piece::RPSJokerTypes jokerRep;

public:
    MyPiecePosition(Piece::RPSPiecesTypes type_, MyPoint& position_, Piece::RPSJokerTypes jokerRep_ = Piece::JNotAJoker): type(type_), position(position_), jokerRep(jokerRep_) {};
    const Point& getPosition() const override;
    char getPiece() const override; // R, P, S, B, J or F
    char getJokerRep() const override; // ONLY for Joker: R, P, S or B -- non-Joker may return �#�
};



