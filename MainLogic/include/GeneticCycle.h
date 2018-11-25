#pragma once

/*
 * Main class of the project. There is sellers and buyers, each have genome - set of strategies (with parameters) implemented in BasicStrategies,
 * Runs cycle, on each step all players play with each other, then worst players replaces with childs creating via pairing class. All info are saving into log file via class StatisticCounter.
*/

#include <algorithm>
#include <vector>
#include "../../BasicStrategies/generalStates.h"
#include "../../Player/include/Buyer.h"
#include "../../Player/include/Seller.h"
#include "../../BasicStrategies/BuyerStrategies/AllBuyerStrategies.h"
#include "../../BasicStrategies/SellerStrategies/AllSellerStrategies.h"
#include "../../BasicStrategies/Pairing/allPairing.h"
#include "../../BasicStrategies/Pairing/PairingAbstract.h"
#include "./AuctionGame.h"
#include "StatisticCounter.h"
#include "StrategiesController.h"

class GeneticCycle {
public:
    GeneticCycle(size_t, size_t, size_t, size_t, size_t, size_t, size_t, std::string);
    void runCycle(); //main cycle
    ~GeneticCycle();
private:
    size_t totalSteps; // amount of steps in main cycle
    size_t movesInGame; // amount of steps in one game between seller and buyer
    size_t howMuchToKill; // how many sellers and buyers are going to die on each step of cycle
    std::vector<Player*> buyers; // set of buyers. Player is the base class, which have derived classes Buyer and Seller
    std::vector<Player*> sellers; // set of sellers
    //std::vector<size_t> worstPlayers; // It's never used?? set of players with the worst result on each step.
    PairingAbstract* pairBuyers; // PairingAbstract is abstract class, which has derived classes that implements special function for creating childs in population of players
    PairingAbstract* pairSellers;
    class AuctionGame game; // functor, takes Buyer and Seller, returns vector of moves in game between them
    class StatisticCounter stats; // class for gathering statistic of game

    void clearProfit(std::vector<Player*>&); // clears amount of money each player won on the step of the cycle
    void destroyWorstPlayers(std::vector<Player*>& players); // destroying players with the worst result on each step of the cycle
    StrategiesController controller;
    RandomNumberGenerator randomNumberGenerator;
};