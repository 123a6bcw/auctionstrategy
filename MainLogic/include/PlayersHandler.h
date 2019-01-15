#pragma once

//TODO unused includes
//TODO comment

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

class PlayersHandler {
public:
    PlayersHandler(size_t, size_t, size_t, size_t, size_t, size_t, size_t, size_t);

    class RandomNumberGenerator randomNumberGenerator;
    class StrategiesController controller; // TODO comment
    size_t movesInGame; // amount of steps in one game between seller and buyer
    size_t howMuchToKill; // how many sellers and buyers are going to die on each step of cycle
    size_t scenarioNumber; //TODO comment

    std::vector<Player*> buyers; // set of buyers. Player is the base class, which have derived classes Buyer and Seller
    std::vector<Player*> sellers; // set of sellers
    PairingAbstract* pairSellers; // PairingAbstract is abstract class, which has derived classes that implements special function for creating childs in population of players
    PairingAbstract* pairBuyers;

    void clearProfit(); //clears amount of money all players won on the step of the cycle
    void clearProfit(std::vector<Player*>&); // clear amount of money won either sellers or buyers
    void destroyWorstPlayers(std::vector<Player*>&); // destroying players with the worst result on each step of the cycle
    void pairPlayers();

    void createStandartScenario(size_t, size_t);

    inline std::vector<Player*>* getSellers() {
        return &sellers;
    };

    inline std::vector<Player*>* getBuyers() {
        return &buyers;
    }

    inline Player* getSeller(size_t s) {
        return sellers[s];
    }

    inline Player* getBuyer(size_t b) {
        return buyers[b];
    }
    ~PlayersHandler();
};