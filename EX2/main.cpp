#include "RPS.h"
#include "Parser.h"
#include "MyMove.h"
#include "GameManager.h"
#include "FileAlgorithm.h"
#include "AutoAlgorithm.h"

int main() {
    unique_ptr<PlayerAlgorithm> alg_1 = make_unique<FileAlgorithm>();
    unique_ptr<PlayerAlgorithm> alg_2 = make_unique<FileAlgorithm>();
    unique_ptr<PlayerAlgorithm> alg_3 = make_unique<AutoAlgorithm>();
    unique_ptr<PlayerAlgorithm> alg_4 = make_unique<AutoAlgorithm>();
//    unique_ptr<PlayerAlgorithm> alg_3 = make_unique<AutoAlgorithm>();
//    GameManager manager(std::move(alg_1), std::move(alg_2));
    GameManager manager(std::move(alg_1), std::move(alg_2));
    return 0;
}

