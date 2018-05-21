#pragma once
#include "FightInfo.h"
#include "Piece.h"
#include "MyPoint.h"
#include <iostream>


//--------------------------
// FightInfo Interface
//--------------------------
// abstract class FightInfo should be the base class for your "FightInfo" implementation
// sent from "Game" to PlayerAlgorithm in 2 flows:
// "Game" -> PlayerAlgorithm : notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
// "Game" -> PlayerAlgorithm : notifyFightResult(const FightInfo& fightInfo);
// Note that "Game" is in parantheses because this is your class and you can choose its name

class MyFightInfo: public FightInfo {
private:
    MyPoint point;
    Piece::RPSPiecesTypes piece1;
    Piece::RPSPiecesTypes piece2;
    int winner;

public:
    MyFightInfo(MyPoint &point_, Piece::RPSPiecesTypes piece_1, Piece::RPSPiecesTypes piece_2, int winner_);
    const Point& getPosition() const override ;
    char getPiece(int player) const override ; // R, P, S, B or F (but NOT J)
    int getWinner() const; // 0 - both lost / tie, 1 - player 1 won, 2 - player 2 won
    void setWinner(int winner_);
    void setPiece(Piece::RPSPiecesTypes piece_);
};



