#include "RPS.h"

class Moves {
public:
	bool move(RPS& rps, int fRow, int fCol, int toRow, int toCol, int player);
	bool parseMoves(int playerIndex);
};