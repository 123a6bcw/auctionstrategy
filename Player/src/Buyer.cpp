#include "../include/Buyer.h"

/*
 * player who accepts (or refuses) proposed deal.
 */

Buyer::Buyer(const Buyer* b) : Player(b), profit(b -> profit) {}

Buyer::Buyer(size_t _movesInGame, int _profit) : Player(_movesInGame), profit(_profit) {
    if (movesInGame == 0) {
        throw std::runtime_error("there cannot be zero moves in one game");
    }

    currentMove = 0;
    currentStrategy = 0;
    totalGain = 0;
    strategies = std::vector<StrategyAbstract*>(0);

    //TODO for now buyer plays only one simple strategy for entire game.
    strategies.push_back(new BSimple(this, 0, movesInGame - 1, profit));
}

Player* Buyer::copy() const {
    auto copyBuyer = new Buyer(this);
    copyBuyer -> strategies = copyStrategies(copyBuyer);
    return copyBuyer;
}

/*
 * Main function. Just throws this request to his current strategy and increment current move
*/
bool Buyer::acceptDeal(int price) {
    /*
     * getCurrentStrategy returns abstract base class AbstractStrategy with derived abstract classes Buyer/SellerAbstractStrategy. Buyer should only use BuyerAbstractStrategy, so
     * using dynamic_cast (should be) safe here.
    */
    bool answer = dynamic_cast<BuyerStrategyAbstract*>(getCurrentStrategy()) -> acceptDeal(price);
    shiftMove();
    return answer;
}

/*
 * If buyer buys something for price P, he gain (profit - P) money there profit is his secret parameter
 */
void Buyer::addGain(int price) {
    totalGain += profit - price;
}