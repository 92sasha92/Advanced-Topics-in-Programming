#include "RPS.h"
#include "Parser.h"
#include "Moves.h"
#include "MyMove.h"
#include "GameManager.h"
#include "FileAlgorithm.h"
#include "AutoAlgorithm.h"

int main() {
//    FileAlgorithm alg1, alg2;
//    AutoAlgorithm alg3, alg4;
    unique_ptr<PlayerAlgorithm> alg_1 = make_unique<FileAlgorithm>();
    unique_ptr<PlayerAlgorithm> alg_2 = make_unique<FileAlgorithm>();
    unique_ptr<PlayerAlgorithm> alg_3 = make_unique<AutoAlgorithm>();
    unique_ptr<PlayerAlgorithm> alg_4 = make_unique<AutoAlgorithm>();
//    unique_ptr<PlayerAlgorithm> alg_3 = make_unique<AutoAlgorithm>();
//    GameManager manager(std::move(alg_1), std::move(alg_2));
    GameManager manager(std::move(alg_3), std::move(alg_4));
    return 0;
}

