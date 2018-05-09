#pragma once
#include "PlayerAlgorithm.h"
#include "MyBoard.h"
#include <stdlib.h>
#include <time.h>
#include <climits>
#include "RPS.h"
#include "MyPoint.h"
#include "MyMove.h"
#include "MyPiecePosition.h"


class AutoAlgorithm: public PlayerAlgorithm  {
private:
    int player;
    int opponent;
    int opponentNumOfFlags;
//    int opponentNumOfNonMovingPieces;  // TODO: maintain opponent not moving pieces instead of unknown pieces
    int opponentNumOfUnknownPieces;
    bool isOpponentAttacked;
    MyMove lastMove;
    std::vector<std::vector<std::unique_ptr<Piece>>> selfGameBoard;

    const int TIE = 0;
    const int EMPTY_CELL = 0;
    const int GAME_NOT_OVER = 3;
    const int FLAG_SCORE = 100;
    const int BOMB_SCORE = 1;
    const int JOKER_SCORE = 5;
    const int SIMPLE_PIECE_SCORE = 1;
    const int WIN_SCORE = INT_MAX;
    const int LOSE_SCORE = INT_MIN;
    const int TIE_SCORE = -1000;

    int scoringFunction(int player); // calculate the board score
    int getPieceScore(unique_ptr<Piece> &piece);
    int getUnknownPieceTypeScore(); // As a function of the number of flags remaining in relation to the unknown pieces
    bool isMoveLegal(unique_ptr<Move> &move); // checks if a move is legal. maybe take or copy from GameManager

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



