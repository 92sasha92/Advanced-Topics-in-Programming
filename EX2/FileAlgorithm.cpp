#include "FileAlgorithm.h"

string FileAlgorithm::player1Moves = "player1.rps_moves";
string FileAlgorithm::player2Moves = "player2.rps_moves";

FileAlgorithm::FileAlgorithm(): moveFile(nullptr), player(0), fileLine(0), jokerChange(nullptr){}

void FileAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
    this->player = player;
    this->fileLine = 0;
    RPS rps;
    EndOfGameHandler endOfGameHandler;

    if (this->player == 1) {
        moveFile.open(player1Moves);
    } else if (this->player == 2) {
        moveFile.open(player2Moves);
    }

    Parser::parseBoard(rps, player, endOfGameHandler, vectorToFill);
}

void FileAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {
    //not relevant for the file algorithm
}

void FileAlgorithm::notifyOnOpponentMove(const Move &move) {
    //not relevant for the file algorithm
}

void FileAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
    //not relevant for the file algorithm
}

unique_ptr<JokerChange> FileAlgorithm::getJokerChange() {
    return move(this->jokerChange);
}

void FileAlgorithm::ParseJokerChange(vector<string> pieceDescription) {
    int col, row;
    char type;
    this->jokerChange = nullptr;
    if (pieceDescription[4].compare("J:")) {
        cout << "ERROR: Joker line format should start with 'J:'" << endl;
        return;
    }

    if (Parser::isInteger(pieceDescription[5])) {
        col = stoi(pieceDescription[5]) - 1;
    } else {
        cout << "incorrect Joker line format" << endl;
        return;
    }

    if (Parser::isInteger(pieceDescription[6])) {
        row = stoi(pieceDescription[6]) - 1;
    } else {
        return;
    }

    if (pieceDescription[7].size() != 1) {
        return;
    }
    type = pieceDescription[7][0];

    MyPoint p(col, row);
    this->jokerChange->init(p, Piece::fromTypeRepToJRep(Piece::getEnumTypeRep(type)));

}

bool FileAlgorithm::isNumOfArgsCorrect(vector<string> &line_words,int fileLine, EndOfGameHandler& endOfGameHandler) {
    if (line_words.size() != 4 && line_words.size() != 8) {
        cout << "ERROR: num of arguments is incorrect" << line_words.size() << endl;
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::BadMoveFile);
        endOfGameHandler.setWinner(this->player, fileLine, fileLine); // TODO: should get fileLine of player1 and player2
        return false;
    }
    return true;
}

void FileAlgorithm::parseMove(vector<string> pieceDescription, unique_ptr<MyMove> &move) {
    int arr[4];
    for (int i = 0; i < 4; i++) {
        if (Parser::isInteger(pieceDescription[i])) {
            arr[i] = stoi(pieceDescription[i]) - 1;
        } else {
            cout << "incorrect line format" << endl;
            return;
        }
    }
    // arr[1] = fRow, arr[0] = fCol, arr[3] = toRow, arr[2] = toCol
//    cout << arr[1] << " " << arr[0] << " " << arr[3] << " " << arr[2] << " player:" << this->player + 1 << endl;
    MyPoint p1(arr[0], arr[1]), p2(arr[2], arr[3]);
    move->init(p1, p2);
}

unique_ptr<Move> FileAlgorithm::getMove() {
    unique_ptr<MyMove> move = make_unique<MyMove>();
    EndOfGameHandler endOfGameHandler;
    int fileLine = 0;
    string cur_line;
    vector<string> line_words;

    if (!moveFile.is_open()) {
        cout << "ERROR: file didn't opened" << endl;
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::BadMoveFile);
        return nullptr;
    }

    if (!moveFile.eof()) {
        try {
            getline(moveFile, cur_line);
        } catch (std::ifstream::failure &e) {
            cout << "ERROR: could not read the next line from the move file" << endl;
            endOfGameHandler.setEndOfGameReason(EndOfGameHandler::BadMoveFile);
            endOfGameHandler.setWinner(player, fileLine, fileLine); // TODO: should get fileLine of player1 and player2
            return nullptr;
        }
        Parser::clearLine(line_words, cur_line);
        if (line_words.size() != 0) {
            if (!isNumOfArgsCorrect(line_words, fileLine, endOfGameHandler)) {
                return nullptr;
            }
            parseMove(line_words, move);
            if (line_words.size() == 8) {
                ParseJokerChange(line_words);
            }
        }
    }
    fileLine++;
    return std::move(move);
}

