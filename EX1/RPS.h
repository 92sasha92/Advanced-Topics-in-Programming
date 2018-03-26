#ifndef RPS_RPS_H
#define RPS_RPS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class RPS {
  private:

    static const int kM_ = 10;
    static const int kN_ = 10;
    static const int kR_ = 2;
    static const int kP_ = 5;
    static const int kS_ = 1;
    static const int kB_ = 2;
    static const int kJ_ = 2;
    static const int kF_ = 1;

    typedef enum {
        kRock,
        kPaper,
        kScissors,
        kBomb,
        kJoker,
        kFlag
    } RPSPieces;

    const static string player_1_name_;
    const static string player_2_name_;

    bool SetPiece(vector<string> piece_description);

  public:

    void Parser(RPS& rps_board_, int player_number);
    char board[kM_][kN_];

//    RPS() : board(NULL) {}
//    ~RPS() {
//        if (board != NULL) {
//            delete[] board;
//        }
//    }

};


#endif //RPS_RPS_H
