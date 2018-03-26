#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "RPS.h"

using namespace std;

bool RPS::SetPiece(vector<string> piece_description) {

}

void RPS::Parser(RPS& rps_board_, int player_number) {
    string cur_line, word;
    bool check;
    ifstream fin;
    vector<string> line_words;

    if (player_number == 1) {
        fin.open(player_1_name_);
    } else if (player_number == 2) {
        fin.open(player_2_name_);
    } else {
        // TODO: raise relevant error (probably not needed)
    }

    while (!fin.eof()) {
        getline(fin, cur_line);
        istringstream ss(cur_line);

        while (getline(ss,word,' ')) {
            line_words.push_back(word);
        }

        check = SetPiece(line_words);
        if (!check) {
            // TODO: raise relevant error
        }

    }

    // TODO: check if need to close ss
    fin.close();
}


