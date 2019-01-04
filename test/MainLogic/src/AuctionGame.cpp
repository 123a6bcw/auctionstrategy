#include "../include/AuctionGame.h"

/*
 * functor that plays game between two players, count their gain and return vector of all moves in game - pair of int price set be seller and bool - was this deal accepted or not
 * pmove is defined inside generalStates.h
 */

std::vector<pmove>* AuctionGame :: operator () (Seller* seller, Buyer* buyer, size_t totalMoves) {
    allMoves.clear();
    buyer -> newGame(&allMoves); // Assigns fields such as current move.
                                 // Also each player should have a link to vector with results of previous moves, because their strategies (may) depend on it
    seller -> newGame(&allMoves);
    
    for (size_t i = 0; i < totalMoves; i++) {
        int price = seller -> setPrice();
        bool result = buyer -> acceptDeal(price);
        allMoves.emplace_back(price, result);
        
        if (result) {
            seller -> addGain(price);
            buyer -> addGain(price);
        }
    }

    return &allMoves;
}