#include "RPS.h"
#include "Parser.h"
#include "MyMove.h"
#include "GameManager.h"
#include "FileAlgorithm.h"
#include "TournamentManager.h"
#include <string>
#include <cstring>


int main(int argc, char* argv[]) {
    int numOfThreads = 4;
    std::string path = "";
    Parser::parseCommandLine(argc, argv, numOfThreads, path);
    TournamentManager::getInstance().setTournamentParameters(path, numOfThreads);
    TournamentManager::getInstance().run();
    return 0;
}

