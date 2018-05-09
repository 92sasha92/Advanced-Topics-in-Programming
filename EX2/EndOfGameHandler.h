#pragma once
#include <iostream>
#include <sstream>

using namespace std;

class EndOfGameHandler {
  public:
    typedef enum {
        GameNotFinished,
        LooserAllFlagsEaten,
        AllMovingPiecesEaten,
        TieAllFlagsEaten,
		TieAllMovingPiecesEaten,
        BadInputFile,
        BadMoveFile,
        CantOpenInputFile
    } EndOfGameReason;

    typedef enum {
        Tie,
        Player1Win,
        Player2Win,
        GameNotOver,
    } GameState;

    EndOfGameHandler() : endOfGameReason(GameNotFinished), gameState(GameNotOver), endGamelineNumber(0) {}
    ~EndOfGameHandler() = default;

    int getEndGamelineNumber();
    void setEndGamelineNumber(int line_number);
    EndOfGameReason getEndOfGameReason();
    void setEndOfGameReason(EndOfGameReason reason);
    GameState getGameState();
    void setGameState(GameState state);
    void setWinner(int currentTurn ,int fileLinePlayer1, int fileLinePlayer2);
    static bool isInputFileOk(const bool isBadInputFile[2]);
    void clear();
    string toString();


  private:
    EndOfGameReason endOfGameReason;
    GameState gameState;
    int endGamelineNumber;
};



