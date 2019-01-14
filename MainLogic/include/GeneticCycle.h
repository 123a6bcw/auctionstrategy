#pragma once

/*
 * Main class of the project. There is sellers and buyers, each have genome - set of strategies (with parameters) implemented in BasicStrategies,
 * Runs cycle, on each step all players play with each other, then worst players replaces with childs creating via pairing class. All info are saving into log file via class StatisticCounter.
*/

#include <algorithm>
#include <vector>
#include <thread>
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
    GeneticCycle(size_t, size_t, size_t, size_t, size_t, size_t, size_t, std::string, size_t, size_t);
    void runCycle(); //main cycle
    ~GeneticCycle();
private:
    void runPartedCycle(size_t, size_t);
    void createPartition(size_t, size_t, std::vector<std::pair<size_t, size_t>>*) const;
    void clearProfit(std::vector<Player*>&) const; // clears amount of money each player won on the step of the cycle
    void destroyWorstPlayers(std::vector<Player *> &players); // destroying players with the worst result on each step of the cycle

    size_t totalSteps; // amount of steps in main cycle
    size_t movesInGame; // amount of steps in one game between seller and buyer
    size_t howMuchToKill; // how many sellers and buyers are going to die on each step of cycle
    std::vector<Player*> buyers; // set of buyers. Player is the base class, which have derived classes Buyer and Seller
    std::vector<Player*> sellers; // set of sellers
    //std::vector<size_t> worstPlayers; // It's never used?? set of players with the worst result on each step.
    PairingAbstract* pairSellers; // PairingAbstract is abstract class, which has derived classes that implements special function for creating childs in population of players
    PairingAbstract* pairBuyers;
    RandomNumberGenerator randomNumberGenerator;

    const size_t ptrNumber; // amount of threads in cycle
    std::vector< std::pair<size_t, size_t> > buyersParts; // partition of buyers into prtNumber parts
    std::vector< std::pair<size_t, size_t> > sellersParts;
    std::vector<std::vector<std::vector<pmove>>> moves; //moves[a][b] --- moves in game between a and b in current genetic cycle
    class StatisticCounter stats; // class for gathering statistic of game
    StrategiesController controller; // TODO comment
    size_t scenarioNumber; //TODO comment
    void createStandartScenario(size_t, size_t); //TODO comment
};