#pragma once

#include <string>
#include <iostream>

class Piece
{
  private:
    int playerNumber;
		int canMove;
  protected:
		void setCanMove(bool isMovable);
  public:
    Piece(int playerNumber);
    int getPlayerNumber();
		int getCanMove();
    virtual std::string toString();
    ~Piece();
};

