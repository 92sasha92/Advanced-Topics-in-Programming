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
    int playerNum(GameManager::Turns const &currentTurn);
    bool handleATurn(GameManager::Turns &currentTurn, EndOfGameHandler& endOfGameHandler, int fileLinePlayer[2], int &numOfMovesWithoutAFight);
    void startGame();
    unique_ptr<MyFightInfo> fight(unique_ptr<PiecePosition> &player1PiecePos, unique_ptr<PiecePosition> &player2PiecePos);
    unique_ptr<MyFightInfo> setPiece(unique_ptr<PiecePosition> &piecePos, int player);
    unique_ptr<MyFightInfo> makeMove(unique_ptr<Move> &pieceMove, int player);
    bool checkJokerChangeAndSet(const JokerChange& jokerChange, int player);
    bool checkLegalPositioningVec(const std::vector<unique_ptr<PiecePosition>> &vec, int &errorLineCounter);
    void checkMovablePieces(bool &player1HaveFlag, bool &player2HaveFlag, bool &player1HaveMovingPieces, bool &player2HaveMovingPieces);
    EndOfGameHandler checkWinner(EndOfGameHandler& endOfGameHandler, int currentPlayer);
    void printBoard();
    void createOutFile(EndOfGameHandler& endOfGameHandler, bool isBadInputFile[2], int ErrorLine[2]);
    Turns changeTurn(Turns turn);

public:
    GameManager(unique_ptr<PlayerAlgorithm> &&player1Algorithm_, unique_ptr<PlayerAlgorithm> &&player2Algorithm_);
};



