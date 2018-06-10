//#include <pair>
#include <string>

#include "ex4.h"
#include "unit_test_util.h"

using std::string;
using std::get;
using std::cout;
using std::endl;

static bool test1(){
	GameBoard<12, 7, string, 4> board;
	int i = 0;
	for (int row = 0; row < 12; row++){
		for(int col = 0; col < 7; col++){
			board.setPiece(row, col, "Piece", i);
			i = (i+1)%4;
		}
	}
	for (int row = 0; row < 12; row++){
		for(int col =0; col < 7; col++){
			if(board.getPiece(row, col) != nullptr){
				std::cout << board.getPiece(row, col)->first << " " << board.getPiece(row, col)->second << std::endl;
			}
		}
	}
	int occurence[4]= {0,0,0,0};
	for(auto pieceInfo : board){
		cout << "row: " << std::get<0>(pieceInfo) << endl;
		cout << "col: " << std::get<1>(pieceInfo) << endl;
		cout << "piece: " << std::get<2>(pieceInfo) << endl; // we assume here that GAME_PIECE implemented <<
		cout << "player: " << std::get<3>(pieceInfo) << endl;
		occurence[get<3>(pieceInfo)]++;
	}
	for(int i = 0;i<4;i++){
		if (occurence[i] != 21){
			return false;
		}
	}
	return true;
}

int main(){
	RUN_TEST(test1);
	return 0;
}