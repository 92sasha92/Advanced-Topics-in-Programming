#include "RPS.h"
#include "Parser.h"
#include "MyMove.h"
#include "GameManager.h"
#include "FileAlgorithm.h"
#include "RSPPlayer_204251599.h"

int main(int argc, char* argv[]) {
    std::string gameMode;
    unique_ptr<PlayerAlgorithm> alg_1, alg_2;
    if (argc < 2) {
        cout << "ERROR: game mode was not specified" << endl;
        cout << "As default we will play auto-vs-auto" << endl; // TODO: maybe return 0, and not set a default game.
        gameMode = "auto-vs-auto";
    } else {
        if (argc != 2) {
            cout << "ERROR: too much arguments received" << endl;
        }
        gameMode = std::string(argv[1]);
        cout << "Game mode set to " << gameMode << "." << endl;
    }

    if (gameMode.compare("auto-vs-auto") == 0) {
        alg_1 = make_unique<RSPPlayer_204251599>();
        alg_2 = make_unique<RSPPlayer_204251599>();
    } else if (gameMode.compare("auto-vs-file") == 0) {
        alg_1 = make_unique<RSPPlayer_204251599>();
        alg_2 = make_unique<FileAlgorithm>();
    } else if (gameMode.compare("file-vs-auto") == 0) {
        alg_1 = make_unique<FileAlgorithm>();
        alg_2 = make_unique<RSPPlayer_204251599>();
    } else if (gameMode.compare("file-vs-file") == 0) {
        alg_1 = make_unique<FileAlgorithm>();
        alg_2 = make_unique<FileAlgorithm>();
    } else {
        cout << "ERROR: Wrong game mode was specified" << endl;
        return 0;
    }
    GameManager manager(std::move(alg_1), std::move(alg_2));
    return 0;
}

