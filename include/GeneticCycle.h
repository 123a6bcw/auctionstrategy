#pragma once

#include "./Buyer.h"
#include "./Seller.h"
#include "../BuyerStrategies/AllBuyerStrategies.h"
#include "../BuyerStrategies/AllSellerStrategies.h"

class GeneticCycle {
public:
    GeneticCycle(int);
    constructPlayers();
    void improveStrategies();
    void cycle();
private:
    int totalMoves;
    vector<Buyer> buyers;
    vector<Seller> sellers;
}
