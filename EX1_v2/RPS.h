#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "PieceFactory.h"
#include "JokerPiece.h"
#include "EndOfGameHandler.h"

using namespace std;

class RPS {
  private:

    static const int Mcols = 10;
    static const int Nrows = 10;
    static const int R = 2;
    static const int P = 5;
    static const int S = 1;
    static const int B = 2;
    static const int J = 2;
    static const int F = 1;
	static const int numOfPlayers = 2;

    int playerPiecesArsenal[7];
    static string outputFile;

    friend class Parser;

  public:

    static void fight(RPS& rps, int row, int col);
    static void printBoard(RPS& rps);
    int getNumberOfRows() const;
    int getNumberOfColumns() const;
    static EndOfGameHandler checkWinner(RPS& rps, EndOfGameHandler& endOfGameHandler, int currentPlayer);
    static void createOutFile(RPS& rps, EndOfGameHandler& endOfGameHandler, bool isBadInputFile[2], int ErrorLine[2]);

    Piece *board[Nrows][Mcols][2];

    RPS();
    RPS(const RPS& rps) = delete;
    RPS& operator=(const RPS& rps) = delete;
    ~RPS();
};



