#pragma once

#include "Board.h"
#include "PieceFactory.h"
#include "Point.h"
#include <vector>
#include <memory>
#include "RPS.h"


class MyBoard: public Board {
private:
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    friend class GameManager;
    friend class AutoAlgorithm;

public:
    MyBoard();
    int getPlayer(const Point& pos) const override;
};



