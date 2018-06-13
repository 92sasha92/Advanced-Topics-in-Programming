#include <string>
#include <utility>

#include "ex4_header.h"
#include "unit_test_util.h"

using std::string;
using std::get;
using std::cout;
using std::endl;

static bool test1(){
	GameBoard<12, 7, string, 4> board;
	int i = 0;
	for (int row = 0; row < 12; row++){
		for(int col =0; col < 7; col++){
			board.setPiece(row, col, "Piece", i);
			i = (i+1)%4;
		}
	}
	int occurence[4]= {0,0,0,0};
	for(auto pieceInfo : board){
		occurence[get<3>(pieceInfo)]++;
	}
	for(int i = 0;i<4;i++){
		if (occurence[i] != 21){
			return false;
		}
	}
	return true;
}

static bool test2(){
	GameBoard<12, 7, char, 4> board;
	int i = 0;
	for (int row = 0; row < 4; row++){
		for(int col = 0; col < 7; col++){
			board.setPiece(row, col, 'p', i);
			i = (i+1)%4;
		}
	}
//	for (int row = 7; row < 12; row++){
//		for(int col = 0; col < 7; col++){
//			board.setPiece(row, col, 'k', i);
//			i = (i+1)%4;
//		}
//	}

//	cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
//
//	int occurence[4]= {0,0,0,0};
//	for(auto pieceInfo : board){
//		cout << "row: " << std::get<0>(pieceInfo) << endl;
//		cout << "col: " << std::get<1>(pieceInfo) << endl;
//		cout << "piece: " << std::get<2>(pieceInfo) << endl; // we assume here that GAME_PIECE implemented <<
//		cout << "player: " << std::get<3>(pieceInfo) << endl;
//		occurence[get<3>(pieceInfo)]++;
//	}
//	for(int i = 0;i<4;i++){
//		if (occurence[i] != 21){
//			return false;
//		}
//	}

	cout << "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" << endl;

    int playerNum = 1;
    int j = 0;
    for(auto pieceInfo : board.allPiecesOfPlayer(playerNum)) {
        cout << "row: " << std::get<0>(pieceInfo) << endl;
        cout << "col: " << std::get<1>(pieceInfo) << endl;
        cout << "piece: " << std::get<2>(pieceInfo) << endl; // we assume here that GAME_PIECE implemented <<
        cout << "player: " << std::get<3>(pieceInfo) << endl;
        j++;
    }
    if(j != 7){
    	return false;
    }
	cout << "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc" << endl;

	char piece = 'k';
	for(auto pieceInfo : board.allOccureneceOfPiece(piece)) {
		cout << "row: " << std::get<0>(pieceInfo) << endl;
        cout << "col: " << std::get<1>(pieceInfo) << endl;
        cout << "piece: " << std::get<2>(pieceInfo) << endl;
        cout << "player: " << std::get<3>(pieceInfo) << endl;
	}

	cout << "ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd" << endl;

	playerNum = 1;
	piece = 'k'; // we assume in this case that GAME_PIECE is char
	for(auto pieceInfo : board.allOccureneceOfPieceForPlayer(piece, playerNum)) {
		cout << "row: " << std::get<0>(pieceInfo) << endl;
        cout << "col: " << std::get<1>(pieceInfo) << endl;
        cout << "piece: " << std::get<2>(pieceInfo) << endl;
        cout << "player: " << std::get<3>(pieceInfo) << endl;
	}

	return true;
}

int main(){
	RUN_TEST(test1);
	RUN_TEST(test2);
	return 0;
}