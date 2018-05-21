#pragma once

#include "RPS.h"
#include <memory>
#include "MyPiecePosition.h"
#include "MyPoint.h"


class Parser {
  private:
    static string player_1_name;
    static string player_2_name;
    static void handleParseError(ifstream& fin, EndOfGameHandler& endOfGameHandler, int playerIndex, int fileLine, vector< unique_ptr<PiecePosition> > &vectorToFill); // handle errors using the EndOfGameHandler object
    static bool parsePiece(RPS& rps, vector<string> piece_description, vector<unique_ptr<PiecePosition>> &vectorToFill); // parse the a line of the board file and check correctness of the format for setting a piece
  public:
	static void split(vector<string> &line_words, string &cur_line); // split the sting to words and push them into the vector
	static bool isInteger(string str); // checks if the string represent an integer
    static void parseBoard(RPS& rps, int playerNumber, EndOfGameHandler& endOfGameHandler, vector< unique_ptr<PiecePosition> > &vectorToFill); // parse the board file of the player and check correctness of the file format
};

