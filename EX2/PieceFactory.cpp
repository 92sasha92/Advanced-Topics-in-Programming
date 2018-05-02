#include "PieceFactory.h"
#include "RockPiece.h"
#include "PaperPiece.h"
#include "ScissorsPiece.h"
#include "BombPiece.h"
#include "JokerPiece.h"
#include "FlagPiece.h"

Piece::RPSPiecesTypes PieceFactory::charToPieceType(char c) {
    switch (c) {
        case 'R':return Piece::RPSPiecesTypes::Rock;
        case 'P':return Piece::RPSPiecesTypes::Paper;
        case 'S':return Piece::RPSPiecesTypes::Scissors;
        case 'B':return Piece::RPSPiecesTypes::Bomb;
        case 'J':return Piece::RPSPiecesTypes::Joker;
        case 'F':return Piece::RPSPiecesTypes::Flag;
        default: {
            std::cout << "ERROR: unspported piece character" << std::endl;
            return Piece::RPSPiecesTypes::Undefined;
        }
    }

}


std::unique_ptr<Piece> PieceFactory::createPiece(Piece::RPSPiecesTypes pieceType, int player, Piece::RPSPiecesTypes jokerPiece) {
    switch (pieceType) {
        case Piece::Rock:
            return  std::make_unique<RockPiece>(player);
        case Piece::Paper:
            return std::make_unique<PaperPiece>(player);
        case Piece::Scissors:
            return std::make_unique<ScissorsPiece>(player);
        case Piece::Bomb:
            return std::make_unique<BombPiece>(player);
        case Piece::Joker:
            return std::make_unique<JokerPiece>(player, jokerPiece);
        case Piece::Flag:
            return std::make_unique<FlagPiece>(player);
        default: {
            std::cout << "ERROR: undefined piece type" << std::endl;
            return nullptr;
        }
    }
}

