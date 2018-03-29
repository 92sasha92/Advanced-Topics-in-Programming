#pragma once

#include <string>
#include <iostream>

class Piece
{
  public:
	typedef enum {
		Rock,
		Paper,
		Scissors,
		Bomb,
		Flag,
		Joker,
		Undefined
	} RPSPiecesTypes;

	typedef enum {
		Weaker,
		Equal,
		Stronger
	} PiecesPower;

    RPSPiecesTypes type;

    Piece (int playerNumber);
    PiecesPower isStrongerThan(const Piece& rival);
    int getPlayerNumber();
    int getCanMove();
    virtual std::string toString();
	~Piece();

  protected:
    PiecesPower strongerThan[5];
    void setCanMove(bool isMovable);

  private:
	int playerNumber;
	int canMove;
};

