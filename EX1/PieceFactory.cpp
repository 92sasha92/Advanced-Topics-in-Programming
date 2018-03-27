#include "PieceFactory.h"
#include "Rock.h"
#include "Paper.h"
#include "Scissors.h"
#include "Joker.h"
#include "Flag.h"

PieceFactory::RPSPiecesTypes PieceFactory::charToPieceType(char c)
{
	switch (c) {
	case 'R':
		return PieceFactory::RPSPiecesTypes::Rock;
	case 'P':
		return PieceFactory::RPSPiecesTypes::Paper;
	case 'S':
		return PieceFactory::RPSPiecesTypes::Scissors;
	case 'B':
		return PieceFactory::RPSPiecesTypes::Bomb;
	case 'J':
		return PieceFactory::RPSPiecesTypes::Joker;
	case 'F':
		return PieceFactory::RPSPiecesTypes::Flag;
	default:
		// TODO: handle unsported piece character
	}

}

Piece *PieceFactory::createPiece(PieceFactory::RPSPiecesTypes pieceType, int player, PieceFactory::RPSPiecesTypes jokerPiece)
{
	switch (pieceType) {
	case Rock:
		return new Rock(player);
	case Paper:
		return new Paper(player);
	case Scissors:
		return new Scissors(player);
	case Bomb:
		return new Bomb(player);
	case Joker:
		return new Joker(player, jokerPiece);// joker can be only R P S B
	case Flag:
		return new Flag(player);
	default:
		// TODO: undefined piece
	}
}

