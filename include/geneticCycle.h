#pragma once

#include "./Buyer.h"
#include "./Seller.h"
#include "../BuyerStrategies/AllBuyerStrategies.h"
#include "../BuyerStrategies/AllSellerStrategies.h"

class geneticCycle {
public:
    geneticCycle(int);
    void improveStrategies();
private:
    int totalMoves;
    vector<Buyer> buyers;
    vector<Seller> players;
}
