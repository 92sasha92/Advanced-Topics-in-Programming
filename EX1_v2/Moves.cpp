#include "Moves.h"

Moves::Move::Move(int fRow, int fCol, int toRow, int toCol, int player) {
	this->fRow = fRow;
	this->fCol = fCol;
	this->toRow = toRow;
	this->toCol = toCol;
	this->player = player;
}

string Moves::player1Moves = "/Users/guy/school/Advanced-Topics-in-Programming/EX1_v2/player1.rps_moves";
string Moves::player2Moves = "/Users/guy/school/Advanced-Topics-in-Programming/EX1_v2/player2.rps_moves";


bool Moves::movePiece(RPS & rps, Moves::Move& move)
{
	if (move.fRow >= 0 && move.fCol >= 0 && move.toCol >= 0 && move.toRow >= 0) {
		cout << "ERROR: problem with the indexes";
		return false;
	}
	Piece *piece = rps.board[move.fRow][move.fCol][move.player];
	if (piece == nullptr) {
		cout << "ERROR: no piece in the given position";
		return false;
	}
	if (!(piece->getCanMove())) {
		cout << "ERROR " << piece->toString() << "can't move" << endl;
		return false;
	}

	return false;
}

Moves::Move* Moves::parseMove(RPS& rps, int playerIndex, vector<string> pieceDescription) {
	int arr[4];
	for (int i = 0; i < 4; i++) {
		if (Parser::isInteger(pieceDescription[i])) {
				arr[i] = stoi(pieceDescription[i]) - 1;		
		} else {
			// TODO: uncorrect line format
			cout << "uncorrect line format" << endl;
			return false;
		}
	}
	return new Move(arr[0], arr[1], arr[2], arr[3], playerIndex);
}


bool Moves::parseMoves(RPS& rps)
{
	string cur_line, word;
	ifstream fin1, fin2;
	bool check;
	Move *move;
	vector<string> line_words;
	fin1.open("player1.rps_moves");
	fin2.open("player2.rps_moves");

	if (!fin1.is_open() || !fin2.is_open()) {
		cout << "ERROR: file didn't opened";
		return false;
	}
	int currentTurn = 0;
	while (!fin1.eof() && !fin2.eof()) {
		if (currentTurn == 0) {
			getline(fin1, cur_line);
		} else {
			getline(fin2, cur_line);
		}
		
		istringstream ss(cur_line);
		line_words.clear();
		while (getline(ss, word, ' ')) {
			if (word.compare("") != 0) {
				//                cout << "word: " << word << ";" << endl;
				line_words.push_back(word);
			}
		}
		if (line_words.size() != 4) {
			// TODO: error, not enogh arguments in line
			cout << "ERROR: num of arguments is incorrect" << line_words.size() << endl;
			return false;
		}
		if (line_words[0].compare("J:") ){
			// TODO: joker change
		} else {
			move = parseMove(rps, currentTurn, line_words);
			if (move != nullptr) {
				movePiece(rps, *move);
				free(move);
			} else {
				// ERROR
				cout << "ERROR: in parsing move";
				return false;
			}
		}

		

	}

	if (!fin1.eof()) {
		// ??????
	}
	else if (!fin2.eof()) {
		// ???????
	}
	fin1.close();
	fin2.close();
	return false;
}
