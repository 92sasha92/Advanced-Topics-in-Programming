#include "RPS.h"
#include "Parser.h"
#include "JokerPiece.h"
#include "MyMove.h"

class Moves {
  private:
    static string player1Moves;
    static string player2Moves;

		class JokerSuitChange {
		public:
			int row;
			int col;
			char type;
			JokerSuitChange(int row_, int col_, char type_);
		};

    static void parseMove(int playerIndex, vector<string> pieceDescription, MyMove &move);
    static bool movePiece(RPS & rps, MyMove& move, bool &isJokerDied, int currentPlayer);
		static void movesHandleError(ifstream fins[2], EndOfGameHandler& endOfGameHandler, EndOfGameHandler::EndOfGameReason reason, int fileLinePlayer[2], int currentTurn);
		static void movesHandleError(ifstream fins[2], EndOfGameHandler& endOfGameHandler, EndOfGameHandler::EndOfGameReason reason);
		static bool isNumOfArgsCorrect(int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler);
		static JokerSuitChange* parseJokerSuitChange(vector<string> pieceDescription);
		static bool setNewJokerSuit(RPS& rps, Moves::JokerSuitChange& suitChange, int player);
		static bool checkJokerChangeAndSet(RPS& rps, int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler, bool &isJokerDied);
		static bool checkMoveAndSet(RPS& rps, int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler, bool &isJokerDied);

  public:
    static void parseMoves(RPS& rps, EndOfGameHandler& endOfGameHandler);

};