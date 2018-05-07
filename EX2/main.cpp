#include "RPS.h"
#include "Parser.h"
#include "Moves.h"
#include "MyMove.h"
#include "GameManager.h"
#include "FileAlgorithm.h"

int main() {
    FileAlgorithm alg1, alg2;
    GameManager manager(alg1, alg2);
//    RPS rps;
//    EndOfGameHandler endOfGameHandler;
//    vector<unique_ptr<PiecePosition>> vectorToFill;
//    unique_ptr<Piece> piecePtr;
//    bool isBadInputFile[2] = {false, false};
//    int ErrorLine[2] = {0, 0};
//		for (int j = 0; j < 2; j++) {
//			endOfGameHandler.clear();
//			Parser::parseBoard(rps, j, endOfGameHandler, vectorToFill);
//            for (unsigned int i=0; i< vectorToFill.size(); i++) {
//                piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(vectorToFill[i]->getPiece()), j, Piece::getEnumTypeRep(vectorToFill[i]->getJokerRep()));
//               // cout << "%%%%%%%%%%%%%%%%%%%%  (" << vectorToFill[i]->getPosition().getX()<< ", " << vectorToFill[i]->getPosition().getY()<< ")" << endl;
//                if (rps.game[vectorToFill[i]->getPosition().getY()][vectorToFill[i]->getPosition().getX()].get() != nullptr) {
//                    if(rps.game[vectorToFill[i]->getPosition().getY()][vectorToFill[i]->getPosition().getX()]->getPlayerNumber() != j){
//                        RPS::fight(rps, vectorToFill[i]->getPosition().getY(),vectorToFill[i]->getPosition().getX(), piecePtr);
//                    } else {
//                        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::BadInputFile);
//                        endOfGameHandler.setWinner(j, i + 1, i + 1);
//                        piecePtr.release();
//                        break;
//                    }
//
//                } else {
//                    rps.game[vectorToFill[i]->getPosition().getY()][vectorToFill[i]->getPosition().getX()] = move(piecePtr);
//                }
//                piecePtr.release();
////         cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~: " << (rps.game[vectorToFill[i]->getPosition().getY()][vectorToFill[i]->getPosition().getX()])->toString() << endl;
//            }
//            vectorToFill.clear();
//
//			if (endOfGameHandler.getEndOfGameReason() == EndOfGameHandler::BadInputFile) {
//				isBadInputFile[j] = true;
//				ErrorLine[j] = endOfGameHandler.getEndGamelineNumber();
//			} else if (endOfGameHandler.getEndOfGameReason() == EndOfGameHandler::CantOpenInputFile) {
//				return 0;
//			}
//		}
//       RPS::checkWinner(rps, endOfGameHandler, 0);
//
//    if (EndOfGameHandler::isInputFileOk(isBadInputFile)) {
//        RPS::printBoard(rps);
//        Moves::parseMoves(rps, endOfGameHandler);
//    }
//
//    RPS::createOutFile(rps, endOfGameHandler, isBadInputFile, ErrorLine);
////    cout << "AND THE WINNER NUMBER IS: " << RPS::checkWinner(rps, endOfGameHandler).getGameState() << endl;
    return 0;
}

