#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "PieceFactory.h"
#include "JokerPiece.h"

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

    int playerPiecesArsenal[7];
    static string outputFile;

    friend class Parser;

  public:

    typedef enum {
        Tie,
        Player1Win,
        Player2Win,
        GameNotOver
    } GameState;

    static void fight(RPS& rps, int row, int col);
    static void printBoard(RPS& rps);
    int getNumberOfRows();
    int getNumberOfColumns();
    static GameState checkWinner(RPS& rps);
    static void createOutFile(RPS& rps);

    Piece *board[Nrows][Mcols][2];

    RPS();
    RPS(const RPS& rps) = delete;
    RPS& operator=(const RPS& rps) = delete;
    ~RPS();

};



