
#include "TournamentManager.h"

TournamentManager TournamentManager::theTournamentManager;

void TournamentManager::run()const {
    for(auto& pair : id2factory) {
        const auto& id = pair.first;
        std::cout << id << ": " << std::endl;
//        const auto& factoryMethod = pair.second;
//        factoryMethod()->
    }
}

void TournamentManager::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> &factoryMethod) {
    // TODO: should warn if id is already registered
    id2factory[id] = factoryMethod;
    std::cout << "hi " << id << std::endl;
}

int TournamentManager::getNumOfThreads() const {
    return numOfThreads;
}

void TournamentManager::setNumOfThreads(int t) {
    this->numOfThreads = t;
}

const std::string& TournamentManager::getAlgorithmsPath() {
    return algorithmsPath;
}

void TournamentManager::setAlgorithmsPath(std::string &path) {
    this->algorithmsPath = path;
}

AlgorithmRegistration::AlgorithmRegistration(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
    TournamentManager::getInstance().registerAlgorithm(id, factoryMethod);
}


