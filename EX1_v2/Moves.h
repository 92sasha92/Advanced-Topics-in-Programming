#include "RPS.h"
#include "Parser.h"

class Moves {
  private:
    static string player1Moves;
    static string player2Moves;
    class Move {
      public:
        int fRow;
        int fCol;
        int toRow;
        int toCol;
        int player;
        Move(int fRow_, int fCol_, int toRow_, int toCol_, int player_);
    };
    static Move* parseMove(RPS& rps, int playerIndex, vector<string> pieceDescription);
    static bool movePiece(RPS& rps, Move& move);
  public:
    static bool parseMoves(RPS& rps);

};