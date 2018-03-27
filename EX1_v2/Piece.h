#pragma once

#include <string>
#include <iostream>

class Piece
{
  private:
    int playerNumber;

  public:
    Piece(int playerNumber);
    int getPlayerNumber();
    virtual std::string toString();
    ~Piece();
};

