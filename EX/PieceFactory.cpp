#include "PieceFactory.h"

PieceFactory::RPSPiecesTypes PieceFactory::charToPieceType(char c) {
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
            return PieceFactory::RPSPiecesTypes::Undefined;
            // TODO: handle unsported piece character
    }

}

Piece* PieceFactory::createPiece(PieceFactory::RPSPiecesTypes pieceType, int player, PieceFactory::RPSPiecesTypes jokerPiece) {
    switch (pieceType) {
        case Rock:
            return new RockPiece(player);
        case Paper:
            return new PaperPiece(player);
        case Scissors:
            return new ScissorsPiece(player);
        case Bomb:
            return new BombPiece(player);
        case Joker:
            return new JokerPiece(player, jokerPiece);// joker can be only R P S B
        case Flag:
            return new FlagPiece(player);
        default:
            return nullptr;
            // TODO: undefined piece
    }
}

