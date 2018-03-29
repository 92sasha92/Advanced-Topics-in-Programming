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
		Move(int fRow, int fCol, int toRow, int toCol, int player);
	};
	Move* parseMove(RPS& rps, int playerIndex, vector<string> pieceDescription);
	bool movePiece(RPS& rps, Move& move);
public:
	bool parseMoves(RPS& rps);
	
};