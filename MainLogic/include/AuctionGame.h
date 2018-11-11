#pragma once

/*
 * functor that plays game between two players, count their gain and return vector of all moves in game - pair of int price set be seller and bool - was this deal accepted or not
 */

#include <vector>
#include "../../Player/include/Buyer.h"
#include "../../Player/include/Seller.h"
#include "../../BasicStrategies/generalStates.h"


class AuctionGame {
public:
    //pmove is defined inside generalStates.h
    std::vector<pmove> operator () (Buyer*, Seller*, size_t);
private:
    std::vector<pmove> allMoves; //vector of all moves in game
};