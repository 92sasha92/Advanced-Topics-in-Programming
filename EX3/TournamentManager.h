#pragma once

#include <iostream>
#include <map>

#include "PlayerAlgorithm.h"
#include "BattleInfo.h"
#include "GameManager.h"
#include <thread>
#include <vector>
#include <stack>
#include <cmath>
#include <set>
#include <mutex>
#include <list>
#include <cstring>
#include <atomic>
#include <algorithm>
#include <dlfcn.h>

class TournamentManager {
private:

    const int GROUP_SIZE = 31;
    const int NUM_OF_GAMES_FOR_ALGO = 30;
    const int TIE = 0;
    const int PLAYER_1 = 1;
    const int PLAYER_2 = 2;
    static TournamentManager theTournamentManager;
    int numOfThreads;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
    std::vector<std::pair<std::string, int>> idNumOfBattlesSet;
    std::stack<unique_ptr<BattleInfo>> tournamentSchedule;
    mutex scheduleLock;
    std::map<std::string, std::atomic<int>> scoringTable;
    std::string algorithmsPath;
    std::list<void *> dl_list;

    void createPartialTournament(int shift);
    int getAlgScore(int result, int curPlayer);
    void setMatch(int p1, int p2);
    void printScores();
    void loadAlgos();
    void loadAlgosFullPath();
    void freeDls();
    // private ctor
    TournamentManager(): numOfThreads(4), id2factory(), idNumOfBattlesSet(), tournamentSchedule(), scheduleLock(), scoringTable(), algorithmsPath(""), dl_list() {}

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
    void setTournamentParameters(std::string &path, int numOfThreads);
    void playAGame();
    void createTournamentSchedule();
    ~TournamentManager(){
//        this->freeDls();
    }
};



