#include "./StrategiesController.h"
#include "./Pairing/allPairing.h"
#include "./Pairing/PairingAbstract.h"

/*
 * here is going to be hardcoded creation of strategy by given number
 */
StrategyAbstract* StrategiesController::createSellerStrategy(size_t numberOfStrategy, Player* player, size_t startMove, size_t endMove) {
    switch (numberOfStrategy) {
        case 1:
            return new SBinarySearch(player, startMove, endMove);
            break;
        case 2:
            return new SCompleteRandom(player, startMove, endMove, minProfit, maxProfit);
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
        case 2:
            return new BCompleteRandom(player, startMove, endMove, profit);
            break;
        case 3:
            return new BIncreaseProfit(player, startMove, endMove, profit,
                         profit + randomNumberGenerator->getRandomNumber(minProfit, maxProfit - profit), randomNumberGenerator->getRandomNumber(0, getLength(startMove, endMove)));
            break;
        default:
            throw(std::runtime_error("createBuyerStrategy: Number of strategy is higher than amount of strategies"));
            break;
    }
}

PairingAbstract* StrategiesController::createSellerPairing(size_t numberOfPairing) {
    switch (numberOfPairing) {
        case 1:
            return new PSimple();
            break;
        default:
            throw std::runtime_error("CreateBuyerPairing: wrong number of pairing function");
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

size_t StrategiesController::getNumberOfStrategies(typeOfPlayer type) {
    switch  (type) {
        case SELLER:
            return numberOfSellerStrategies;
            break;
        case BUYER:
            return numberOfBuyerStrategies;
            break;
        default:
            throw(std::runtime_error("?? unknown type of player"));

    }
}

/*
 * creates new strategy by given ID of strategy (index number)
 * this function simply switches by the type of the player, creating either seller or buyer strategy
 */
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

/*
 * absolutely the same hardcoded thing, but for pairing function
 */
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

StrategiesController::StrategiesController(RandomNumberGenerator* randomNumberGenerator) : randomNumberGenerator(randomNumberGenerator) {}