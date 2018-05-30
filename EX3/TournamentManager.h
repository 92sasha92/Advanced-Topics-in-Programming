#pragma once

#include <iostream>
#include <map>
#include "PlayerAlgorithm.h"
#include "AlgorithmRegistration.h"

class TournamentManager {
private:
    static TournamentManager theTournamentManager;
    //std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
    // private ctor
    TournamentManager() {}
public:
    static TournamentManager& getInstance() {
        return theTournamentManager;
    }
    void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);
};



