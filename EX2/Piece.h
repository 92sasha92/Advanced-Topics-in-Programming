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
        JRock,
        JPaper,
        JScissors,
        JBomb,
        JNotAJoker
    } RPSJokerTypes;

	typedef enum {
		Weaker,
		Equal,
		Stronger
	} PiecesPower;

    RPSPiecesTypes type;
    static char getCharTypeRep(RPSPiecesTypes type);
    Piece (int playerNumber);
    PiecesPower isStrongerThan(const Piece& rival);
    int getPlayerNumber();
    virtual int getCanMove();
    virtual std::string toString();
	static char fromJRepToChar(RPSJokerTypes jokerRep);
	static RPSJokerTypes fromTypeRepToJRep(RPSPiecesTypes typeRep);
	static RPSPiecesTypes getEnumTypeRep(char type);
	virtual ~Piece();

  protected:
    PiecesPower strongerThan[5];
    void setCanMove(bool isMovable);

  private:
	int playerNumber;
	int canMove;
};

