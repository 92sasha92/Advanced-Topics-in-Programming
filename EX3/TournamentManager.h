#pragma once

#include <iostream>
#include <map>
#include <thread>
#include <vector>
#include "PlayerAlgorithm.h"
#include "AlgorithmRegistration.h"


class TournamentManager {
private:

    static TournamentManager theTournamentManager;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
    int numOfThreads;
    std::string algorithmsPath;
    // private ctor
    TournamentManager(): id2factory(), numOfThreads(4), algorithmsPath("") {}
public:
    static TournamentManager& getInstance() {
        return theTournamentManager;
    }
    void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> &factoryMethod);
    void run();
    int getNumOfThreads() const;
    void setNumOfThreads(int t);
    const std::string& getAlgorithmsPath();
    void setAlgorithmsPath(std::string &path);
    void playAGame();
    void createTournamentSchedule();
};



