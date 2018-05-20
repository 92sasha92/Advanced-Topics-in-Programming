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
  private:
    friend class Parser;

  public:

	static const int Mcols = 10;
	static const int Nrows = 10;
	static const int R = 2;
	static const int P = 5;
	static const int S = 1;
	static const int B = 2;
	static const int J = 2;
	static const int F = 1;
	int playerPiecesArsenal[7];

	int getNumberOfRows() const;
	int getNumberOfColumns() const;
	void initializePiecesArsenal();
	static bool checkIfMoveIsLegal(std::vector<std::vector<std::unique_ptr<Piece>>> &board, const Move &move, int player, bool printMessages = true);
    RPS(){
    };
    RPS(const RPS& rps) = delete;
    RPS& operator=(const RPS& rps) = delete;
};



