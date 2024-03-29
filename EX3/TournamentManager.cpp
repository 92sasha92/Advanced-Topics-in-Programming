
#include <dirent.h>
#include "TournamentManager.h"

TournamentManager TournamentManager::theTournamentManager;

void TournamentManager::playAGame(){
    unique_lock<mutex> lock(scheduleLock);
//    std::cout << "welcome to playAGame()" << std::endl;
    while(!tournamentSchedule.empty()){
        std::unique_ptr<BattleInfo> battle = std::move(tournamentSchedule.top());
        tournamentSchedule.pop();
        lock.unlock();
        unique_ptr<PlayerAlgorithm> alg_1 = id2factory[battle->getId1()]();
        unique_ptr<PlayerAlgorithm> alg_2 = id2factory[battle->getId2()]();
        GameManager manager(std::move(alg_1), std::move(alg_2));
        int result = manager.startGame();
        int alg1Score = getAlgScore(result, PLAYER_1);
        int alg2Score = getAlgScore(result, PLAYER_2);
        if (battle->getIsAlgo1BattleCount()) {
            scoringTable[battle->getId1()] += alg1Score;
        }
        if (battle->getIsAlgo2BattleCount()) {
            scoringTable[battle->getId2()] += alg2Score;
        }
        lock.lock();
    }
    lock.unlock();
}

int TournamentManager::getAlgScore(int result, int curPlayer) {
    if (result == TIE) {
        return 1;
    } else if (result == curPlayer) {
        return 3;
    }
    return 0;
}

void TournamentManager::setMatch(int p1, int p2) {
    if (p1 == p2) {
        cout << "ERROR: algorithm can't play against itself!" << endl;
        return;
    }

    bool isAlgo1BattleCount = true, isAlgo2BattleCount = true;
    if (idNumOfBattlesSet[p1].second >= NUM_OF_GAMES_FOR_ALGO) {
        isAlgo1BattleCount = false;
    } 
    if (idNumOfBattlesSet[p2].second >= NUM_OF_GAMES_FOR_ALGO) {
        isAlgo2BattleCount = false;
    } 

    if (isAlgo1BattleCount || isAlgo2BattleCount) {
		idNumOfBattlesSet[p1].second++;
		idNumOfBattlesSet[p2].second++;
//		cout << endl << "match between  " << idNumOfBattlesSet[p1].first << " to  " << idNumOfBattlesSet[p2].first <<endl;
        tournamentSchedule.push(std::move(std::make_unique<BattleInfo>(idNumOfBattlesSet[p1].first, idNumOfBattlesSet[p2].first, isAlgo1BattleCount, isAlgo2BattleCount)));
    }
}

void TournamentManager::createTournamentSchedule() {
    int i, start;
    for (i = 0; i < floor(idNumOfBattlesSet.size() / static_cast<double>(GROUP_SIZE)); i++ ) {
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
        }
//        else if (idRepeats.second > NUM_OF_GAMES_FOR_ALGO) {
//            cout << "WARNING: "<< idRepeats.second << " matches for " << idRepeats.first << endl;
//        }
    }
}

void TournamentManager::createPartialTournament(int shift) {
    int numOfElements = idNumOfBattlesSet.size() % GROUP_SIZE ;
//	std::cout << "createPartial" << numOfElements << std::endl;
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

    int numOfRepeats = (int)(ceil(static_cast<double>(GROUP_SIZE) / (numOfElements - 1))), start = shift * GROUP_SIZE;
//	std::cout << "numOfRepeats: " << numOfRepeats << std::endl;
    for (int i = start; i < (int)idNumOfBattlesSet.size(); i++) { // run over the last (less than 31) elements
        for (int j = i + 1; j < (int)idNumOfBattlesSet.size(); j++) {
            for (int k = 0; k < numOfRepeats; k++) {
                setMatch(i, j);
            }
        }
    }
}

void TournamentManager::run(){
    if(!this->algorithmsPath.compare("")){
        this->loadAlgos();
    } else {
        this->loadAlgosFullPath();
    }
//    for(auto& pair : id2factory) {
//        const auto& id = pair.first;
//        std::cout << id << ": " << std::endl;
//    }
    this->createTournamentSchedule();
    auto numOfGames = (int)tournamentSchedule.size();
//	std::cout << "created schedule" << std::endl;
    std::vector<std::thread> ths;
    for (int i = 1; i < min(this->numOfThreads, numOfGames - 1); i++) {
        ths.push_back(std::thread(&TournamentManager::playAGame, this));
    }
	playAGame();

    for (auto& th : ths) {
        th.join();
    }
    printScores();
}



void TournamentManager::loadAlgosFullPath() {
    DIR* dirp = opendir(this->algorithmsPath.c_str());
    if(dirp == nullptr){
        std::cout << "Error: path not valid, could not open directory" << std::endl;
        return;
    }
    struct dirent * dp;
    void *dlib;
    char libName[1024];
    while ((dp = readdir(dirp)) != nullptr) {
        std::string name = dp->d_name;
        std::cout << name << std::endl;
        if(name.size() > 3 && !name.substr(name.size() - 3, 3).compare(".so")){
            sprintf(libName, "%s/%s", this->algorithmsPath.c_str(), name.c_str()); // append ./ to the front of the lib name
            dlib = dlopen(libName, RTLD_LAZY);
            if(dlib == nullptr){
                cout << "ERROR: cannot open dynamic lib " << name << endl;
            } else {
                dl_list.insert(dl_list.end(), dlib); // add the handle to our list
            }
        }

    }
    closedir(dirp);
}

void TournamentManager::freeDls() {
    std::list<void *>::iterator itr;
    for(itr=dl_list.begin(); itr!=dl_list.end(); itr++){ // close all the dynamic libs we opened
        dlclose(*itr);
    }
}

void TournamentManager::loadAlgos() {
    static unsigned int BUF_SIZE = 1024; // size of buffer for reading in directory entries
    FILE *dl;   // handle to read directory
    const char *command_str = "ls *.so";  // command string to get dynamic lib names
    char in_buf[1024]; // input buffer for lib names
    dl = popen(command_str, "r"); // get the names of all the dynamic libs (.so  files) in the current dir
    if(!dl){
        perror("popen");
        cout << "ERROR: cannot get dynamic lib" << endl;
        return;
    }
    void *dlib;
    char name[1024];
    while(fgets(in_buf, BUF_SIZE, dl)){
        char *ws = strpbrk(in_buf, " \t\n");  // trim off the whitespace
        if(ws) *ws = '\0';
        sprintf(name, "./%s", in_buf); // append ./ to the front of the lib name
        dlib = dlopen(name, RTLD_LAZY);
        if(dlib == nullptr){
            cout << "ERROR: cannot open dynamic lib " << name << endl;
        } else {
            dl_list.insert(dl_list.end(), dlib); // add the handle to our list
        }
    }
}

void TournamentManager::registerAlgorithm(std::string &id, std::function<std::unique_ptr<PlayerAlgorithm>()> &factoryMethod) {
    if (id2factory.find(id) != id2factory.end()) {
        cout << "ERROR: id already exist" << endl;
        return;
    }
    id2factory[id] = factoryMethod;
    scoringTable[id] = 0;
    idNumOfBattlesSet.push_back(std::pair<std::string, int>(id, 0));
//    std::cout << "hi " << id << std::endl;
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

void TournamentManager::setTournamentParameters(std::string &path, int numOfThreads) {
    setAlgorithmsPath(path);
    setNumOfThreads(numOfThreads);
}

void TournamentManager::printScores() {
    // Defining a lambda function to compare two pairs. It will compare two pairs using second field
    auto compFunctor = [](std::pair<std::string, int> elem1, std::pair<std::string, int> elem2) {
		return elem1.second != elem2.second ?  elem1.second > elem2.second : elem1.first < elem2.first;
     };

    // Declaring a set that will store the pairs using above comparision logic
    std::set<std::pair<std::string, int>, decltype(compFunctor)> setOfIds(scoringTable.begin(), scoringTable.end(), compFunctor);

    // Iterate over a set using range base for loop, it will display the items in sorted order of values
    for (const auto &element : setOfIds){
        std::cout << element.first << " " << element.second << std::endl;
    }
}


