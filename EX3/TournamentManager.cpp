
#include "TournamentManager.h"

TournamentManager TournamentManager::theTournamentManager;

void TournamentManager::playAGame(){
    std::cout << 1 << std::endl;
// lock the tournamentSchedule
    while(!tournamentSchedule.empty()){
        std::unique_ptr<BattleInfo> battle = std::move(tournamentSchedule.top());
        tournamentSchedule.pop();
        // unlock the tournamentSchedule
        unique_ptr<PlayerAlgorithm> alg_1 = id2factory[battle->getId1()]();
        unique_ptr<PlayerAlgorithm> alg_2 = id2factory[battle->getId2()]();
        GameManager manager(std::move(alg_1), std::move(alg_2));
       // int result = manager.startGame();
        // TODO: lock and update the score

        // TODO: unlock the score struct
        // lock the tournamentSchedule
    }
    // unlock the tournamentSchedule
}

void TournamentManager::setMatch(int p1, int p2) {
    bool isAlgo1BattleCount = true, isAlgo2BattleCount = true;

    if (idNumOfBattlesSet[p1].second >= NUM_OF_GAMES_FOR_ALGO) {
        isAlgo1BattleCount = false;
    }
    if (idNumOfBattlesSet[p2].second >= NUM_OF_GAMES_FOR_ALGO) {
        isAlgo2BattleCount = false;
    }

    idNumOfBattlesSet[p1].second++;
    idNumOfBattlesSet[p2].second++;

    if (isAlgo1BattleCount || isAlgo2BattleCount) {
        tournamentSchedule.push(std::move(std::make_unique<BattleInfo>(idNumOfBattlesSet[p1].first, idNumOfBattlesSet[p2].first, isAlgo1BattleCount, isAlgo2BattleCount)));
    }
}

void TournamentManager::createTournamentSchedule() {
    int i, start;
    for (i = 0; i < floor(idNumOfBattlesSet.size() / GROUP_SIZE); i++ ) {
        start = i * GROUP_SIZE;
        for (int j = start ; j < start + GROUP_SIZE; j++) {
            for (int k = j + 1; k < start + GROUP_SIZE; k++) {
                setMatch(j, k);
            }
        }
    }
    createPartialTournament(i);

    for (auto &idRepeats : idNumOfBattlesSet) {
        if (idRepeats.second < NUM_OF_GAMES_FOR_ALGO) {
            cout << "ERROR: only " << idRepeats.second << " matches for " << idRepeats.first << endl;
        } else if (idRepeats.second > NUM_OF_GAMES_FOR_ALGO) {
            cout << "WARNING: "<< idRepeats.second << " matches for " << idRepeats.first << endl;
        }
    }

    // TODO: update the makefile
}

void TournamentManager::createPartialTournament(int shift) {
    int numOfElements = idNumOfBattlesSet.size() % GROUP_SIZE ;

    if (numOfElements == 0) { // already set all matches
        return;
    } else if (numOfElements == 1) {
        if (shift > 0) { // only one algorithm remain so it will fight one fight against every algorithm in the first group
            for (int p = 0; p < NUM_OF_GAMES_FOR_ALGO; p++) {
                setMatch(idNumOfBattlesSet.size() - 1, p);
            }
            return;
        } else {
            std::cout << "ERROR: TournamentManager got only one algorithm" << std::endl;
            return;
        }
    }

    int numOfRepeats = (int)(ceil(GROUP_SIZE / numOfElements)), start = shift * GROUP_SIZE;
    // TODO: maybe it will be better to run from the end to the start
    for (int i = start; i < (int)idNumOfBattlesSet.size(); i++) { // run over the last (less than 31) elements
        for (int j = i + 1; i < (int)idNumOfBattlesSet.size(); j++) {
            for (int k = 0; k < numOfRepeats; k++) {
                setMatch(i, j);
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
    std::vector<std::thread> ths;
    for (int i = 1; i < this->numOfThreads; i++) {
        ths.push_back(std::thread(&TournamentManager::playAGame, this));
    }

    for (auto& th : ths) {
        th.join();
    }
}

void TournamentManager::registerAlgorithm(std::string &id, std::function<std::unique_ptr<PlayerAlgorithm>()> &factoryMethod) {
    // TODO: should warn if id is already registered
    id2factory[id] = factoryMethod;
    idNumOfBattlesSet.push_back(std::pair<std::string, int>(id, 0));
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


