#include "../include/StrategiesController.h"
#include "../../BasicStrategies/Pairing/allPairing.h"
#include "../../BasicStrategies/Pairing/PairingAbstract.h"

StrategyAbstract* StrategiesController::createStrategy(size_t numberOfStrategy, Player* player, size_t startMove, size_t endMove, int profit, typeOfPlayer type) {
    switch (type) {
        case SELLER:
            return createSellerStrategy(numberOfStrategy, player, startMove, endMove);
            break;
        case BUYER:
            return createBuyerStrategy(numberOfStrategy, player, startMove, endMove, profit);
            break;
        default:
            throw(std::runtime_error("?? unknown type of player"));
    }
}

size_t StrategiesController::getAmmountOfStrategies(typeOfPlayer type) {
    switch  (type) {
        case SELLER:
            return ammountOfSellerStrategies;
            break;
        case BUYER:
            return ammountOfBuyerStrategies;
            break;
        default:
            throw(std::runtime_error("?? unknown type of player"));

    }
}

StrategyAbstract* StrategiesController::createSellerStrategy(size_t numberOfStrategy, Player* player, size_t startMove, size_t endMove) {
    switch (numberOfStrategy) {
        case 1:
            return new SBinarySearch(player, startMove, endMove);
            break;
        default:
            throw(std::runtime_error("createSellerStrategy: Number of strategy is higher than amount of strategies"));
            break;
    }
}

StrategyAbstract* StrategiesController::createBuyerStrategy(size_t numberOfStrategy, Player* player, size_t startMove, size_t endMove, int profit) {
    switch (numberOfStrategy) {
        case 1:
            return new BSimple(player, startMove, endMove, profit);
            break;
        default:
            throw(std::runtime_error("createBuyerStrategy: Number of strategy is higher than amount of strategies"));
            break;
    }
}

PairingAbstract* StrategiesController::createPairing(size_t numberOfPairing, typeOfPlayer type) {
    switch (type) {
        case BUYER:
            return createBuyerPairing(numberOfPairing);
            break;
        case SELLER:
            return createSellerPairing(numberOfPairing);
            break;
        default:
            throw std::runtime_error("create pairing: unknown type of player");
    }
}

PairingAbstract* StrategiesController::createBuyerPairing(size_t numberOfPairing) {
    switch (numberOfPairing) {
        case 1:
            return static_cast<PairingAbstract*>(new PSimple());
            break;
        default:
            throw std::runtime_error("CreateBuyerPairing: wrong number of pairing function");
    }
}

PairingAbstract* StrategiesController::createSellerPairing(size_t numberOfPairing) {
    switch (numberOfPairing) {
        case 1:
            return static_cast<PairingAbstract*>(new PSimple());
            break;
        default:
            throw std::runtime_error("CreateBuyerPairing: wrong number of pairing function");
    }
}