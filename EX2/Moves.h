#include "RPS.h"
#include "Parser.h"
#include "JokerPiece.h"
#include <dirent.h>

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

		class JokerSuitChange {
		public:
			int row;
			int col;
			char type;
			JokerSuitChange(int row_, int col_, char type_);
		};

    static Move* parseMove(int playerIndex, vector<string> pieceDescription);
    static bool movePiece(RPS& rps, Move& move, bool &isJokerDied);
		static void movesHandleError(ifstream fins[2], EndOfGameHandler& endOfGameHandler, EndOfGameHandler::EndOfGameReason reason, int fileLinePlayer[2], int currentTurn);
		static void movesHandleError(ifstream fins[2], EndOfGameHandler& endOfGameHandler, EndOfGameHandler::EndOfGameReason reason);
		static void clearLine(vector<string> &line_words, string &cur_line);
		static bool isNumOfArgsCorrect(int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler);
		static JokerSuitChange* parseJokerSuitChange(vector<string> pieceDescription);
		static bool setNewJokerSuit(RPS& rps, Moves::JokerSuitChange& suitChange, int player);
		static bool checkJokerChangeAndSet(RPS& rps, int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler, bool &isJokerDied);
		static bool checkMoveAndSet(RPS& rps, int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler, bool &isJokerDied);

  public:
    static void parseMoves(RPS& rps, EndOfGameHandler& endOfGameHandler);

};