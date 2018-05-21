#include "MyBoard.h"

int MyBoard::getPlayer(const Point &pos) const {
    if (board[pos.getY()][pos.getX()] != nullptr) {
        return board[pos.getY()][pos.getX()]->getPlayerNumber();
    }
    return 0;
}

MyBoard::MyBoard(): board(0) {
    for (int i = 0; i < RPS::NRows; i++) {
        vector<unique_ptr<Piece>> line;
        for (int j = 0; j < RPS::MCols; j++) {
            unique_ptr<Piece> ptr;
            line.push_back(move(ptr));
        }
        board.push_back(move(line));
    }
}