#include "Moves.h"

bool Moves::move(RPS & rps, int fRow, int fCol, int toRow, int toCol, int player)
{
	if (fRow >= 0 && fCol >= 0 && toCol >= 0 && toRow >= 0) {
		cout << "ERROR: problem with the indexes";
		return false;
	}
	Piece *piece = rps.board[fRow][fCol][player];
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

bool Moves::parseMoves(int playerIndex)
{
	string cur_line, word;
	ifstream fin;
	vector<string> line_words;
	if (playerIndex == 0) {
		fin.open("player1.rps_moves");
	}
	else if (playerIndex == 1) {
		fin.open("player2.rps_moves");
	}
	else {
		// TODO: raise relevant error (probably not needed)
		return false;
	}

	if (!fin.is_open()) {
		cout << "ERROR: file didn't opened";
		return false;
	}

	while (!fin.eof()) {
		getline(fin, cur_line);
		istringstream ss(cur_line);
		line_words.clear();
		while (getline(ss, word, ' ')) {
			if (word.compare("") != 0) {
				//                cout << "word: " << word << ";" << endl;
				line_words.push_back(word);
			}
		}

		if (line_words.size() < 3) {
			// TODO: error, not enogh arguments in line
			cout << "ERROR: not enogh arguments " << line_words.size() << endl;
			return false;
		}

	}

	return false;
}
