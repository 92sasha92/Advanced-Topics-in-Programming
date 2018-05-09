#pragma once
#include "PlayerAlgorithm.h"
#include "MyBoard.h"
#include <stdlib.h>
#include <time.h>
#include "RPS.h"
#include "MyPoint.h"
#include "MyMove.h"
#include "MyPiecePosition.h"


class AutoAlgorithm: public PlayerAlgorithm  {
private:
    int player;
    int opponent;
    int opponentNumOfFlags;
    bool isOpponentAttacked;
    MyMove lastMove;
    MyBoard selfGameBoard;
    const int TIE = 0;

public:
    AutoAlgorithm();
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override ;
    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
    void notifyOnOpponentMove(const Move& move) override; // called only on opponent�s move
    void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
    unique_ptr<Move> getMove() override;
    unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
    ~AutoAlgorithm() {}
};



