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
		static void exitMoves(ifstream &fin1, ifstream &fin2, EndOfGameHandler& endOfGameHandler, EndOfGameHandler::EndOfGameReason reason);
		static void Moves::clearLine(vector<string> &line_words, string &cur_line);
		static void updateLine(int currentTurn, ifstream fins[2], string playerNextLines[2], string &cur_line);
		static bool isNumOfArgsCorrect(int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler);
		static bool checkJokerChangeAndSet(RPS& rps, int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler, string playerNextLines[2]);
		static bool checkMoveAndSet(RPS& rps, int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler, string playerNextLines[2]);
		static bool parsingLeftoverMoves();

  public:
    static void parseMoves(RPS& rps, EndOfGameHandler& endOfGameHandler);

};