#pragma once

#ifndef RPS_RPS_H
#define RPS_RPS_H

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

    const string player_1_name_ = "player1.rps_board";
    const string player_2_name_ = "player2.rps_board";

    bool SetPiece(vector<string> piece_description);

  public:

    void Parser(RPS& rps_board_, int player_number);

//    RPS() : board(NULL) {}
//    ~RPS() {
//        if (board != NULL) {
//            delete[] board;
//        }
//    }

};


#endif //RPS_RPS_H
