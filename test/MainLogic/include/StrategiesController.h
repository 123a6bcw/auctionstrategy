#pragma once

#include <vector>
#include <stdexcept>

#include "../../BasicStrategies/StrategyAbstract.h"
#include "../../BasicStrategies/BuyerStrategies/AllBuyerStrategies.h"
#include "../../BasicStrategies/SellerStrategies/AllSellerStrategies.h"

enum typeOfPlayer { SELLER, BUYER };

class PairingAbstract;

class StrategiesController {
public:
    size_t getAmmountOfStrategies(typeOfPlayer);
    StrategyAbstract* createStrategy(size_t, Player*, size_t, size_t, int, typeOfPlayer);
    PairingAbstract* createPairing(size_t, typeOfPlayer);
private:
    const size_t ammountOfBuyerStrategies = 1;
    const size_t ammountOfSellerStrategies = 1;
    StrategyAbstract* createSellerStrategy(size_t, Player*, size_t, size_t);
    StrategyAbstract* createBuyerStrategy(size_t, Player*, size_t, size_t, int);
    PairingAbstract*  createBuyerPairing(size_t);
    PairingAbstract*  createSellerPairing(size_t);
};