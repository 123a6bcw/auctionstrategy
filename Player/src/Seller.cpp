#include "../include/Seller.h"
#include <algorithm>

/*
 * Player who sets price and proposes deal to buyer
 */

Seller::Seller(const Seller* s) :
Player(s)
{}

Seller::Seller(size_t movesInGame, RandomNumberGenerator* randomNumberGenerator, StrategiesController* controller) :
Player(movesInGame, randomNumberGenerator, controller, SELLER)
{
    totalGain = 0;
}

Seller::Seller(size_t movesInGame, RandomNumberGenerator* randomNumberGenerator, StrategiesController* controller, std::vector<StrategyAbstract*>* strategies) :
Player(movesInGame, randomNumberGenerator, controller, SELLER, strategies)
{
    totalGain = 0;
    currentMove = 0;
    currentStrategy = 0;
}


/*
 * Main function. Just throws this request to his current strategy and increment current move
 */
int Seller::setPrice() {
    /*
     * getCurrentStrategy returns abstract base class AbstractStrategy with derived abstract classes Buyer/SellerAbstractStrategy. Buyer should only use BuyerAbstractStrategy, so
     * using dynamic_cast (should be) safe here.
     */
    int answer = (dynamic_cast<SellerStrategyAbstract*>(getCurrentStrategy())) -> setPrice();
    shiftMove();
    return answer;
}

Player* Seller::copy() const {
    auto copySeller = new Seller(this);
    copySeller -> strategies = copyStrategies(copySeller);
    return copySeller;
}

/*
 * adds how much money he gain (in order to later find players with lowest (or highest) gain).
 */
void Seller::addGain(int price) {
    totalGain += price;
}

Seller::~Seller() = default;
