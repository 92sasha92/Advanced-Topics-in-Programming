
#include "TournamentManager.h"

TournamentManager TournamentManager::theTournamentManager;

void TournamentManager::playAGame(){

}

void TournamentManager::setMatch(int p1, int p2) {
    bool isAlgo1BattleCount = true, isAlgo2BattleCount = true;

    if (idNumOfBattlesSet[p1].second >= 30) {
        isAlgo1BattleCount = false;
    }

    if (idNumOfBattlesSet[p2].second >= 30) {
        isAlgo2BattleCount = false;
    }

    idNumOfBattlesSet[p1].second++;
    idNumOfBattlesSet[p2].second++;

    if (isAlgo1BattleCount || isAlgo2BattleCount) {
        tournamentSchedule.push(std::move(std::make_unique<BattleInfo>(idNumOfBattlesSet[p1], idNumOfBattlesSet[p2], isAlgo1BattleCount, isAlgo2BattleCount)));
    }
}

void TournamentManager::createTournamentSchedule() {
    int i, start;
    for (i = 0; i < floor(idNumOfBattlesSet.size() / 31); i++ ) {
        start = i * 31;
        for (int j = start ; j < start + 31; j++) {
            for (int k = j + 1; k < start + 31; k++) {
                setMatch(j, k);
            }
        }
    }
    createPartialTournament(i);
    // TODO: check that every algorithm have reasonable number of matches
    // TODO: update the makefile
}

void TournamentManager::createPartialTournament(int shift) {
    int numOfElements = idNumOfBattlesSet.size() % 31 ;

    if (numOfElements == 0) { // already set all matches
        return;
    } else if (numOfElements == 1) {
        if (shift > 0) { // only one algorithm remain so it will fight one fight against every algorithm in the first group
            for (int p = 0; p < 30; p++) {
                setMatch(idNumOfBattlesSet.size() - 1, p);
            }
            return;
        } else {
            std::cout << "ERROR: TournamentManager got only one algorithm" << std::endl;
            return;
        }
    }

    int numOfRepeats = (int)(ceil(31 / numOfElements)), start = shift * 31;
    for (int i = start; i < idNumOfBattlesSet.size(); i++) { // run over the last (less than 31) elements
        for (int j = i + 1; i < idNumOfBattlesSet.size(); j++) {
            for (int k = 0; k < numOfRepeats; k++) {
                setMatch(j, k);
            }
        }
    }
}

void TournamentManager::run(){
    for(auto& pair : id2factory) {
        const auto& id = pair.first;
        std::cout << id << ": " << std::endl;
//        const auto& factoryMethod = pair.second;
//        factoryMethod()->
    }
    this->createTournamentSchedule();
//    std::vector<std::thread> ths;
//    for (int i = 1; i <= this->numOfThreads; i++) {
//        ths.push_back(std::thread(&playAGame));
//    }
//
//    for (auto& th : ths) {
//        th.join();
//    }
}

void TournamentManager::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> &factoryMethod) {
    // TODO: should warn if id is already registered
    id2factory[id] = factoryMethod;
    idNumOfBattlesSet.push_back(std::pair(id, 0));
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


