#pragma once

#include "RPS.h"


class Parser {
  private:

    static string player_0_name_;
    static string player_1_name_;

    static void initializePiecesArsenal(RPS& rps);
    static bool setPiece(RPS& rps, int playerNumber, vector<string> piece_description);
    
  public:

	static bool isInteger(string str);
    static bool parseBoard(RPS& rps, int playerNumber);

};

