#pragma once

#include <vector>
#include <stdexcept>

#include "./StrategyAbstract.h"
#include "./BuyerStrategies/AllBuyerStrategies.h"
#include "./SellerStrategies/AllSellerStrategies.h"
#include "./generalStates.h"

/*
 * class for accessing all created strategies
 */

enum typeOfPlayer { SELLER, BUYER };
class PairingAbstract;

class StrategiesController {
public:
    StrategiesController(RandomNumberGenerator*);
    size_t getNumberOfStrategies(typeOfPlayer);
    StrategyAbstract* createStrategy(size_t, Player*, size_t, size_t, int, typeOfPlayer);
    PairingAbstract* createPairing(size_t, typeOfPlayer);
private:
    StrategyAbstract* createSellerStrategy(size_t, Player*, size_t, size_t);
    StrategyAbstract* createBuyerStrategy(size_t, Player*, size_t, size_t, int);
    PairingAbstract*  createBuyerPairing(size_t);
    PairingAbstract*  createSellerPairing(size_t);
    RandomNumberGenerator* rng;

    const size_t numberOfBuyerStrategies  = 3;
    const size_t numberOfSellerStrategies = 2;
};
