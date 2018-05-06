#pragma once

#include "PlayerAlgorithm.h"
#include "RPS.h"
#include "Parser.h"
#include "EndOfGameHandler.h"

class FileAlgorithm: public PlayerAlgorithm {
private:
    ifstream moveFile;
    int player;
    static std::string player1Moves;
    static std::string player2Moves;
    unique_ptr<JokerChange> jokerChange;
public:
    FileAlgorithm();
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
    void notifyOnOpponentMove(const Move& move) override; // called only on opponent�s move
    void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
    unique_ptr<Move> getMove() override;
    unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
    ~FileAlgorithm(){
        moveFile.close();
    };
};



