#include "../include/Seller.h"

/*
 * Player who sets price and proposes deal to buyer
 */

Seller::Seller(const Seller* s) : Player(s) {}

Seller::Seller(size_t mIG) : Player(mIG) {
    totalGain = 0;
    strategies = std::vector<StrategyAbstract*>(0);
    //TODO for now plays only with one simple strategy
    strategies.push_back(new SBinarySearch(this, 0, movesInGame - 1));
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
