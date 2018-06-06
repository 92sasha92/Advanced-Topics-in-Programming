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
#include "MyFightInfo.h"
#include "MyJokerChange.h"
#include "AlgorithmRegistration.h"

class RSPPlayer_204251599: public PlayerAlgorithm  {
private:
    int player;
    int opponent;
    int opponentNumOfFlags;
    int opponentNumOfUnknownPieces;
    bool isOpponentAttacked;
    MyMove lastMove;
    std::vector<std::vector<std::unique_ptr<Piece>>> selfGameBoard;

    const int AUTO_ALGORITHM_DEPTH = 3;
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
    void handleOneOfTheMoveChoice(int row, int col, MyPoint &pTo, MyPoint &bestPFrom, MyPoint &bestPTo, int curPlayer, int &curScore, int &bestScore, MyMove &curMove, int depth, bool isMax, vector<unique_ptr<Move>> &bestMovesVec); // handle move for the recursive function
    int scoringFunction(int player); // calculate the board score
    int getPieceScore(unique_ptr<Piece> &piece) const;
    int getUnknownPieceTypeScore() const; // As a function of the number of flags remaining in relation to the unknown pieces
    EndOfGameHandler checkWinner(EndOfGameHandler& endOfGameHandler, int currentPlayer);
    int swapTurn(int curPlayer);
    void undoMove(MyMove &lastMove, unique_ptr<Piece>& fromPiece, unique_ptr<Piece>& toPiece);
    int recFuncHandler(MyMove &curMove, int curPlayer, int depth, bool isMax); // function handler to calculate the current move result and score
    int recFunc(int curPlayer, int depth, bool isMax); // recursive function that calculate all the options for the next move
    int getScoreForJokerRep(int row, int col, Piece::RPSJokerTypes jokerRep);
    unique_ptr<MyFightInfo> makeMove(unique_ptr<Move> &pieceMove, int player);
    unique_ptr<MyFightInfo> fight(unique_ptr<PiecePosition> &player1PiecePos, unique_ptr<PiecePosition> &player2PiecePos);
    bool indexCheck(int row, int col);
    void notifyFightResultWhenPlayerDefend(const FightInfo& fightInfo, const MyPoint &fLastPoint, const MyPoint &toLastPoint);
    void notifyFightResultWhenPlayerAttack(const FightInfo& fightInfo, const MyPoint &fLastPoint, const MyPoint &toLastPoint);
    void setPieceData(int row, int col , bool &playerHaveFlag, bool &playerHaveMovingPieces);
    void setPointAndGetScore(int row, int col, MyPoint &pTo, MyMove &curMove, int curPlayer, int depth, bool isMax, int &bestScore);
    int getJokerMoveScore(int row, int col, unique_ptr<Piece> &tmpPiece);
    void printBoard();

public:
    RSPPlayer_204251599();
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
    void notifyOnOpponentMove(const Move& move) override; // called only on opponent�s move
    void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
    unique_ptr<Move> getMove() override;
    unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
    ~RSPPlayer_204251599(){};
};



