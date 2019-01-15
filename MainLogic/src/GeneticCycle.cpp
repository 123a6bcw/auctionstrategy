#include "../include/GeneticCycle.h"
#include "../../BasicStrategies/StrategiesController.h"

/*
 * Main class of the project. There is sellers and buyers, each have genome - set of strategies (with parameters) implemented in BasicStrategies,
 * Runs cycle, on each step all players play with each other, then worst players replaces with childs creating via pairing class. All info are saving into log file via class StatisticCounter.
 * gets amount of players in cycle, amount of step in cycle, amount of steps in each playing game, how many players will die on each step of the cycle, two special function for creating
 * childs in population, and string --- name of log file.
*/

GeneticCycle :: GeneticCycle(size_t numberOfSellers, size_t numberOfBuyers, size_t totalSteps, size_t movesInGame, size_t howMuchToKill,
        size_t numberOfBuyerPairing, size_t numberOfSellerPairing, std::string outputFile, size_t ptrNumber, size_t scenarioNumber, size_t seed) :
        playersHandler(seed, movesInGame, howMuchToKill, scenarioNumber, numberOfSellerPairing, numberOfBuyerPairing, numberOfSellers, numberOfBuyers),
        partedGeneticCycle(numberOfSellers, numberOfBuyers, ptrNumber, &playersHandler, movesInGame),
        stats(std::move(outputFile), ptrNumber, &partedGeneticCycle.moves, movesInGame),
        threads(std::vector<std::thread>(0)),
        totalSteps(totalSteps), ptrNumber(ptrNumber)
        {
}

/*
 * main cycle
 */
void GeneticCycle :: runCycle() {
    for (size_t currentStep = 0; currentStep < totalSteps; currentStep++) {
        std::cout << currentStep + 1 << std::endl; //used for tracking progress from GUI
        playersHandler.clearProfit(); //clear amount of money players won on previous step

        stats.newStep(currentStep);
        stats.gather(playersHandler.getSellers(), SELLER); //collects some sort of statistic
        stats.gather(playersHandler.getBuyers(), BUYER);

        for (size_t shift = 0; shift < ptrNumber; shift++) {
            /*
             * for given shift for each x, sellers in part x plays with buyers in part (x + shift) % numberOfParts
             * That way everyone plays with everyone, but for given shift, all players in parts are disjoint, so we can
             * use threads to parallel this process
             */

            threads.clear();
            for (size_t sellerPart = 0; sellerPart < partedGeneticCycle.getSellersPartsLength(); sellerPart++) {
                size_t buyerPart = (sellerPart + shift) % partedGeneticCycle.getBuyersPartsLength();
                threads.emplace_back(std::thread(&PartedGeneticCycle::runPartedCycle, &partedGeneticCycle, sellerPart, buyerPart));
            }

            for (auto& t : threads) {
                t.join();
            }
        }

        stats.gatherFromMoves();
        stats.gatherGain(playersHandler.getSellers(), SELLER);
        stats.gatherGain(playersHandler.getBuyers(), BUYER);

        playersHandler.pairPlayers();
    }
}
