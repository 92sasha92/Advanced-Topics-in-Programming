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
        CantOpenInputFile,
        Tie100MovesNoFight
    } EndOfGameReason;

    typedef enum {
        Tie,
        Player1Win,
        Player2Win,
        GameNotOver,
    } GameState;

    EndOfGameHandler() : endOfGameReason(GameNotFinished), gameState(GameNotOver), endGameLineNumber(0) {}
    ~EndOfGameHandler() = default;

    int getEndGameLineNumber() const; // return the file line number that cause the error
    void setEndGameLineNumber(int line_number); // set the file line number that cause the error
    EndOfGameReason getEndOfGameReason() const;
    void setEndOfGameReason(EndOfGameReason reason);
    GameState getGameState() const; // return the current state of the game
    void setGameState(GameState state);
    void setWinner(int currentTurn ,int fileLinePlayer1, int fileLinePlayer2);
    string toString() const;


  private:
    EndOfGameReason endOfGameReason;
    GameState gameState;
    int endGameLineNumber;
};



