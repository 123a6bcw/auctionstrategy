#include <string>
#include <iostream>
#include "../include/GeneticCycle.h"

//Input data is given through main.py, which will have some GUI

int main(int argc, char* argv[]) {
    size_t numberOfSellers = 5; //static_cast<size_t>(std::stoul(argv[0]))
    size_t numberOfBuyers = 5; //static_cast<size_t>(std::stoul(argv[1]))
    size_t totalSteps = 10; //static_cast<size_t>(std::stoul(argv[2]))
    size_t movesInGame = 10; //static_cast<size_t>(std::stoul(argv[3]))
    size_t howMuchToKill = 2; //static_cast<size_t>(std::stoul(argv[4]))
    PairingAbstract* pairSellers = static_cast<PairingAbstract*>(new PSimple()); // argv[5]
    PairingAbstract* pairBuyers = new PSimple(); // argv[6]
    std::string logFile = "log.txt"; //argv[7]

    try {
        GeneticCycle(numberOfSellers, numberOfBuyers, totalSteps, movesInGame, howMuchToKill, *pairSellers, *pairBuyers, logFile).runCycle();
    }
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}