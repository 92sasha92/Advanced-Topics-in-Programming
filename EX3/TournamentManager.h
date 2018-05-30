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

class TournamentManager {
private:

    static TournamentManager theTournamentManager;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
    std::vector<std::pair<std::string, int>> idNumOfBattlesSet;
    std::stack<unique_ptr<BattleInfo>> tournamentSchedule;
    int numOfThreads;
    std::string algorithmsPath;
    void createPartialTournament(int shift);
    void setMatch(int p1, int p2);
    // private ctor
    TournamentManager(): id2factory(), idNumOfBattlesSet(), tournamentSchedule(), numOfThreads(4), algorithmsPath("") {}

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



