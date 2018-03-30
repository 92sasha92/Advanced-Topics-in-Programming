#include "RPS.h"
#include "Parser.h"
#include "JokerPiece.h"

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
        Move(int fCol_, int fRow_, int toCol_, int toRow_, int player_);
    };

    static Move* parseMove(RPS& rps, int playerIndex, vector<string> pieceDescription);
    static bool movePiece(RPS& rps, Move& move);
    static bool setNewJokerPiece(RPS& rps, vector<string> pieceDescription, int player);

  public:
    static void parseMoves(RPS& rps, EndOfGameHandler& endOfGameHandler);

};