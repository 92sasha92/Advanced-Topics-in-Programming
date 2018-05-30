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
    static char getCharTypeRep(RPSPiecesTypes type); // convert the piece type from RPSPiecesTypes to char
    Piece (int playerNumber);
    PiecesPower isStrongerThan(const Piece& rival);
    int getPlayerNumber() const;
    virtual int getCanMove() const; // return 0 if the piece cant move (by definition, like bomb) and 1 otherwise
    virtual std::string toString() const;
	static char fromJRepToChar(RPSJokerTypes jokerRep); // convert the piece type from RPSJokerTypes to char
	static RPSJokerTypes fromTypeRepToJRep(RPSPiecesTypes typeRep); // convert the piece type from RPSPiecesTypes to RPSJokerTypes
	static RPSPiecesTypes getEnumTypeRep(char type); // convert the piece type from char to RPSPiecesTypes
	virtual ~Piece();

  protected:
    PiecesPower strongerThan[5];
    void setCanMove(bool isMovable); //set 0 if the piece cant move (by definition, like bomb) and 1 otherwise

  private:
	int playerNumber;
	int canMove;
};

