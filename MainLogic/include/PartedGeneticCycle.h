#pragma once

//TODO: comment
//TODO: unused includes

#include <algorithm>
#include <vector>
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

class PartedGeneticCycle {
public:
    PartedGeneticCycle(size_t, size_t, size_t, PlayersHandler*, size_t);
    PlayersHandler* playersHandler;
    std::vector< std::pair<size_t, size_t> > sellersParts; // partition of buyers into prtNumber parts
    std::vector< std::pair<size_t, size_t> > buyersParts;
    std::vector<std::vector<std::vector<pmove>>> moves; //moves[a][b] --- moves in game between a and b in current genetic cycle
    size_t movesInGame;

    void createPartition(size_t, size_t, std::vector<std::pair<size_t, size_t>>*);
    void runPartedCycle(size_t, size_t);

    inline size_t getSellersPartsLength() {
        return sellersParts.size();
    }

    inline size_t getBuyersPartsLength() {
        return buyersParts.size();
    }
};