#pragma once
#include "PlayerAlgorithm.h"
#include <vector>
#include <memory>
#include "MyBoard.h"
#include "MyPoint.h"
#include "MyFightInfo.h"
#include "MyPiecePosition.h"
#include "MyMove.h"
#include "MyJokerChange.h"

class GameManager {
private:
    static string outputFile;
    vector<unique_ptr<PlayerAlgorithm>> playerAlgorithms;
    MyBoard gameBoard;
    typedef enum {
        FIRST_PLAYER_TURN = 0,
        SECOND_PLAYER_TURN = 1
    }Turns;

    int playerNum(GameManager::Turns const &currentTurn); // return the current player number
    bool handleATurn(GameManager::Turns &currentTurn, EndOfGameHandler& endOfGameHandler, int fileLinePlayer[2], int &numOfMovesWithoutAFight);

    unique_ptr<MyFightInfo> fight(unique_ptr<PiecePosition> &player1PiecePos, unique_ptr<PiecePosition> &player2PiecePos); // handle the fight
    unique_ptr<MyFightInfo> setPiece(unique_ptr<PiecePosition> &piecePos, int player); // set piece on board
    unique_ptr<MyFightInfo> makeMove(unique_ptr<Move> &pieceMove, int player); // make the move
    bool checkJokerChangeAndSet(const JokerChange& jokerChange, int player);
    bool checkLegalPositioningVec(const std::vector<unique_ptr<PiecePosition>> &vec, int &errorLineCounter); // check that the moves vector is legal
    void checkMovablePieces(bool &player1HaveFlag, bool &player2HaveFlag, bool &player1HaveMovingPieces, bool &player2HaveMovingPieces);
    EndOfGameHandler checkWinner(EndOfGameHandler& endOfGameHandler, int currentPlayer); // check if there is a winner
    void printBoard();
    void createOutFile(EndOfGameHandler& endOfGameHandler, bool isBadInputFile[2], int ErrorLine[2]); // write the result to the output file
    Turns changeTurn(Turns turn);
    void checkAndSetBoolFlags(Piece * const currentPiece, bool &playerHaveFlag, bool &playerHaveMovingPieces);
    bool checkAndSetInitPiecePos(int errorLine[2], bool isBadInputVec[2], std::vector<unique_ptr<FightInfo>> &fightInfoVec);
    bool handleErrorInAMove(GameManager::Turns &currentTurn, EndOfGameHandler& endOfGameHandler, unique_ptr<Move> &movePtr, int fileLinePlayer[2]);

public:
    GameManager(unique_ptr<PlayerAlgorithm> &&player1Algorithm_, unique_ptr<PlayerAlgorithm> &&player2Algorithm_);
    int startGame(); // control the game flow
};



