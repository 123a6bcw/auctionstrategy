#include "../include/BSimple.h"
#include "../../../Player/include/Player.h"

/*
 * simplest strategy for buyer. Accepts deal if his gain isn't negative.
 */

BSimple::BSimple(const BSimple* bs) : BuyerStrategyAbstract(bs) {}

void BSimple::reset() {
    // strategy does not have any parameters to reset
}

bool BSimple::acceptDeal(int price) {
    return price < profit;
}

StrategyAbstract* BSimple::copy(Player* player) const {
    auto copyStrategy = new BSimple(this);
    copyStrategy -> owner = player;
    return copyStrategy;
}

void BSimple::randomParametersChange() {
  // strategy does not have any parameters to change
}

BSimple::~BSimple() {

}
