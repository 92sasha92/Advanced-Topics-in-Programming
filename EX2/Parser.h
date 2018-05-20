#pragma once

#include "RPS.h"
#include <memory>
#include "MyPiecePosition.h"
#include "MyPoint.h"


class Parser {
  private:
    static string player_1_name;
    static string player_2_name;
    static void handleParseError(ifstream& fin, EndOfGameHandler& endOfGameHandler, int playerIndex, int fileLine, vector< unique_ptr<PiecePosition> > &vectorToFill);
    static bool parsePiece(RPS& rps, vector<string> piece_description, vector<unique_ptr<PiecePosition>> &vectorToFill);
  public:
	static void split(vector<string> &line_words, string &cur_line);
	static bool isInteger(string str);
    static void parseBoard(RPS& rps, int playerNumber, EndOfGameHandler& endOfGameHandler, vector< unique_ptr<PiecePosition> > &vectorToFill);
};

