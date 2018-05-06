#include "FileAlgorithm.h"

string FileAlgorithm::player1Moves = "player1.rps_moves";
string FileAlgorithm::player2Moves = "player2.rps_moves";

void FileAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
    this->player = player;
    RPS rps;
    EndOfGameHandler endOfGameHandler;
    Parser::parseBoard(rps, player, endOfGameHandler, vectorToFill);
}

void FileAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {
    if (this->player == 1) {
        moveFile.open(player1Moves);
    } else if (this->player == 2) {
        moveFile.open(player2Moves);
    }
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

unique_ptr<Move> FileAlgorithm::getMove() {
    //TODO: implement, need to manage the joker parsing as well
    return nullptr;
}

