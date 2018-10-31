#pragma once

#include "./Buyer.h"
#include "./Seller.h"
#include "../BuyerStrategies/AllBuyerStrategies.h"
#include "../BuyerStrategies/AllSellerStrategies.h"

class GeneticCycle {
public:
    GeneticCycle(int, int, int, int, BuyerPairingAbstract&, SellerPairingAbstract&);
    void improveStrategies();
    void cycle();
private:
    int totalSteps;
    int movesInGame;
    int howMuchToKill;
    vector<Buyer> buyers;
    vector<Seller> sellers;
    vector<int> worstPlayers;
    BuyerPairingAbstract& pairBuyers; 
    SellerPairingAbstract& pairSellers;
}
