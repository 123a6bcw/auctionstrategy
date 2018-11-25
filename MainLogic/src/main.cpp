#include <string>
#include <iostream>
#include "../include/GeneticCycle.h"

//Input data is given through main.py, which will have some GUI

int main(int argc, char* argv[]) {
    size_t numberOfSellers = static_cast<size_t>(std::stoul(argv[1]));
    size_t numberOfBuyers = static_cast<size_t>(std::stoul(argv[2]));
    size_t totalSteps = static_cast<size_t>(std::stoul(argv[3]));
    size_t movesInGame = static_cast<size_t>(std::stoul(argv[4]));
    size_t howMuchToKill = static_cast<size_t>(std::stoul(argv[5]));
    size_t pairSellers = static_cast<size_t>(std::stoul(argv[6]));
    size_t pairBuyers = static_cast<size_t>(std::stoul(argv[7]));
    std::string logFile = argv[8];
    
    try {
        GeneticCycle(numberOfSellers, numberOfBuyers, totalSteps, movesInGame, howMuchToKill, pairSellers, pairBuyers, logFile).runCycle();
    }
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
