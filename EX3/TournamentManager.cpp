
#include "TournamentManager.h"

TournamentManager TournamentManager::theTournamentManager;

void TournamentManager::playAGame(){
    std::cout << 1 << std::endl;
}

void TournamentManager::createTournamentSchedule(){

}

void TournamentManager::run(){
    for(auto& pair : id2factory) {
        const auto& id = pair.first;
        std::cout << id << ": " << std::endl;
//        const auto& factoryMethod = pair.second;
//        factoryMethod()->
    }
    this->createTournamentSchedule();
    std::vector<std::thread> ths;
    for (int i = 1; i < this->numOfThreads; i++) {
        ths.push_back(std::thread(&TournamentManager::playAGame, this));
    }

    for (auto& th : ths) {
        th.join();
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


