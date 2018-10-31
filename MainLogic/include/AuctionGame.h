#pragma once

#include ".../Player/include/Buyer.h"
#include ".../Player/include/Seller.h"
#include ".../BasicStrategies/generalStates.h"

class AuctionGame {
public:
    AuctionGame(vector<pmove> t) : allMoves(t) {};
    void operator () (Buyer&, Seller&, int)
    vector<pmove> getAllMoves() const;
private:
    vector<pmove> allMoves;
}
