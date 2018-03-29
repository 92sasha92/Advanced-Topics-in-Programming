#pragma once

#include <string>
#include <iostream>
#include "PieceFactory.h"

class Piece
{
  private:
    int playerNumber;
	int canMove;

  protected:
    PieceFactory::RPSPiecesTypes type;
    char strongerThan[5];
    void setCanMove(bool isMovable);

  public:

    typedef enum {
        Weaker,
        Equal,
        Stronger
    } PiecesPower;

    Piece (int playerNumber);
    int getPlayerNumber();
		int getCanMove();
    virtual std::string toString();
    ~Piece();
};

