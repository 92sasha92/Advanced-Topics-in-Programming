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

    EndOfGameHandler() : endGamelineNumber(0), endOfGameReason(GamePlaying), gameState(GameNotOver) {}
    ~EndOfGameHandler() = default;

    int getEndGamelineNumber();
    void setEndGamelineNumber(int line_number);
    EndOfGameReason getEndOfGameReason();
    void setEndOfGameReason(EndOfGameReason reason);
    GameState getGameState();
    void setGameState(GameState state);
    static void setWinner(int currentTurn ,int fileLinePlayer1, int fileLinePlayer2);


  private:
    EndOfGameReason endOfGameReason;
    GameState gameState;
    int endGamelineNumber;
};



