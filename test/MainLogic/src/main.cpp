#include <string>
#include <iostream>
#include "../include/GeneticCycle.h"

//Input data is given through main.py, which will have some GUI

int main(int argc, char* argv[]) {
    
    size_t numberOfSellers, numberOfBuyers, totalSteps, movesInGame, howMuchToKill, pairSellers, pairBuyers;
    std::string logFile;
    
    if (strcmp(argv[1], "-debug") == 0) {
        numberOfSellers = 10;
        numberOfBuyers = 10;
        totalSteps = 10;
        movesInGame = 10;
        howMuchToKill = 5;
        pairSellers = 1;
        pairBuyers = 1;
        logFile = "debugLog.txt";
    } else {
        numberOfSellers = static_cast<size_t>(std::stoul(argv[1]));
        numberOfBuyers = static_cast<size_t>(std::stoul(argv[2]));
        totalSteps = static_cast<size_t>(std::stoul(argv[3]));
        movesInGame = static_cast<size_t>(std::stoul(argv[4]));
        howMuchToKill = static_cast<size_t>(std::stoul(argv[5]));
        pairSellers = static_cast<size_t>(std::stoul(argv[6]));
        pairBuyers = static_cast<size_t>(std::stoul(argv[7]));
        logFile = argv[8];
    }
    try {
        GeneticCycle(numberOfSellers, numberOfBuyers, totalSteps, movesInGame, howMuchToKill, pairSellers, pairBuyers, logFile).runCycle();
    }
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
