#pragma once

/*
 * Main class of the project. There is sellers and buyers, each have genome - set of strategies (with parameters) implemented in BasicStrategies,
 * Runs cycle, on each step all players play with each other, then worst players replaces with childs creating via pairing class. All info are saving into log file via class StatisticCollector.
*/

#include <algorithm>
#include <vector>
#include <thread>
#include "PartedGeneticCycle.h"
#include "PlayersHandler.h"
#include "../../BasicStrategies/generalStates.h"
#include "../../Player/include/Buyer.h"
#include "../../Player/include/Seller.h"
#include "../../BasicStrategies/BuyerStrategies/AllBuyerStrategies.h"
#include "../../BasicStrategies/SellerStrategies/AllSellerStrategies.h"
#include "../../BasicStrategies/Pairing/allPairing.h"
#include "../../BasicStrategies/Pairing/PairingAbstract.h"
#include "./AuctionGame.h"
#include "StatisticCollector.h"
#include "../../BasicStrategies/StrategiesController.h"

class GeneticCycle {
public:
    GeneticCycle(size_t, size_t, size_t, size_t, size_t, size_t, size_t, std::string, size_t, size_t, size_t);
    void runCycle(); //main cycle
private:
    class PlayersHandler playersHandler;
    class PartedGeneticCycle partedGeneticCycle;
    class StatisticCollector stats;
    std::vector<std::thread> threads; //TODO comment

    size_t totalSteps; // amount of steps in main cycle
    const size_t ptrNumber; // amount of threads in cycle
};