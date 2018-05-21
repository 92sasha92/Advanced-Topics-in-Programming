#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include "PieceFactory.h"
#include "JokerPiece.h"
#include "EndOfGameHandler.h"
#include "PiecePosition.h"
#include "Move.h"
#include "MyPoint.h"

using namespace std;

class RPS {
    public:

	static const int MCols = 10;
	static const int NRows = 10;
	static const int R = 2;
	static const int P = 5;
	static const int S = 1;
	static const int B = 2;
	static const int J = 2;
	static const int F = 1;
	int playerPiecesArsenal[7];

	// expected zero based point
	static bool isPointInBounds(const Point &point); // checks if the piece location is in the board bounds
	void initializePiecesArsenal(); // initialize the playerPiecesArsenal array acording to the game settings
	// expected zero based move
	static bool checkIfMoveIsLegal(std::vector<std::vector<std::unique_ptr<Piece>>> &board, const Move &move, int player, bool printMessages = true);
    RPS() {};
    RPS(const RPS& rps) = delete;
    RPS& operator=(const RPS& rps) = delete;
};



