#pragma once

#include <iostream>
#include <map>

#include "PlayerAlgorithm.h"
#include "AlgorithmRegistration.h"
#include "BattleInfo.h"
#include "GameManager.h"
#include <thread>
#include <vector>
#include <stack>
#include <cmath>
#include <set>

class TournamentManager {
private:
    const int GROUP_SIZE = 31;
    const int NUM_OF_GAMES_FOR_ALGO = 30;
    const int TIE = 0;
    const int PLAYER_1 = 1;
    const int PLAYER_2 = 2;

    int numOfThreads;
    static TournamentManager theTournamentManager;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
    std::vector<std::pair<std::string, int>> idNumOfBattlesSet;
    std::stack<unique_ptr<BattleInfo>> tournamentSchedule;
    std::map<std::string, int> scoringTable;
    std::string algorithmsPath;

    void createPartialTournament(int shift);
    int getAlgScore(int result, int curPlayer);
    void setMatch(int p1, int p2);
    void updateScoringTable(bool isAlgoScoreCount, std::string &algoName, int algoScore);
    void printScores();
    // private ctor
    TournamentManager(): id2factory(), idNumOfBattlesSet(), tournamentSchedule(), scoringTable(), numOfThreads(4), algorithmsPath("") {}

public:
    static TournamentManager& getInstance() {
        return theTournamentManager;
    }
    void registerAlgorithm(std::string &id, std::function<std::unique_ptr<PlayerAlgorithm>()> &factoryMethod);
    void run();
    int getNumOfThreads() const;
    void setNumOfThreads(int t);
    const std::string& getAlgorithmsPath();
    void setAlgorithmsPath(std::string &path);
    void playAGame();
    void createTournamentSchedule();
};



