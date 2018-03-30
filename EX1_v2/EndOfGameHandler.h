#pragma once

class EndOfGameHandler {
  public:
    typedef enum {
        GamePlaying,
        LooserAllFlagsEaten,
        AllMovingPiecesEaten,
        GmaeOverWithoutWinner,
        TieAllFlagsEaten,
        BadInputFile,
        BadMoveFile,
        NoInputFile,
        NoMoveFile
    } EndOfGameReason;

    typedef enum {
        Tie,
        Player1Win,
        Player2Win,
        GameNotOver,
    } GameState;

    EndOfGameHandler() : endOfGameReason(GamePlaying), gameState(GameNotOver), endGamelineNumber(0) {}
    ~EndOfGameHandler() = default;

    int getEndGamelineNumber();
    void setEndGamelineNumber(int line_number);
    EndOfGameReason getEndOfGameReason();
    void setEndOfGameReason(EndOfGameReason reason);
    GameState getGameState();
    void setGameState(GameState state);
    void setWinner(int currentTurn ,int fileLinePlayer1, int fileLinePlayer2);


  private:
    EndOfGameReason endOfGameReason;
    GameState gameState;
    int endGamelineNumber;
};



