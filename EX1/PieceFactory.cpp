#include "PieceFactory.h"

RPSPiecesTypes charToPieceType(char c)
{
	switch (c) {
	case 'R':
		return RPSPiecesTypes::Rock;
	case 'P':
		return RPSPiecesTypes::Paper;
	case 'S':
		return RPSPiecesTypes::Scissors;
	case 'B':
		return RPSPiecesTypes::Bomb;
	case 'J':
		return RPSPiecesTypes::Joker;
	case 'F':
		return RPSPiecesTypes::Flag;
	default:
		// TODO: handle unsported piece character
	}

}

Piece *createPiece(RPSPiecesTypes pieceType, int player, RPSPiecesTypes jokerPiece)
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

