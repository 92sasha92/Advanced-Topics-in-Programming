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

    friend class Parser;

  public:

    static void fight(RPS& rps, int row, int col);
    void printBoard();
    Piece *board[Nrows][Mcols][2];

    RPS();
    //    ~RPS() {
    //        if (board != NULL) {
    //            delete[] board;
    //        }
    //    }

};



