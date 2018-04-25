#pragma once

#include "RPS.h"
#include <memory>
#include "MyPiecePosition.h"
#include "MyPoint.h"


class Parser {
  private:

    static string player_0_name_;
    static string player_1_name_;

    static void initializePiecesArsenal(RPS& rps);
		static void handleParseError(ifstream& fin, EndOfGameHandler& endOfGameHandler, int playerIndex, int fileLine);
    static bool setPiece(RPS& rps, int playerNumber, vector<string> piece_description, vector<unique_ptr<PiecePosition>> &vectorToFill);
    
  public:
		static void clearLine(vector<string> &line_words, string &cur_line);
	  static bool isInteger(string str);
    static void parseBoard(RPS& rps, int playerNumber, EndOfGameHandler& endOfGameHandler);
	static void printVector(vector<unique_ptr<PiecePosition>> &vector);

};

