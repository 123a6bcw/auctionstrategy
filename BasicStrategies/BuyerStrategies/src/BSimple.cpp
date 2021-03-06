#include "../include/BSimple.h"
#include "../../../Player/include/Player.h"

/*
 * simplest strategy for buyer. Accepts deal if his gain isn't negative.
 */

BSimple::BSimple(const BSimple* anotherStrategy):
BuyerStrategyAbstract(anotherStrategy)
{}

void BSimple::reset() {
    // strategy does not have any parameters to reset
}

bool BSimple::acceptDeal(int price) {
    return price < profit;
}

void BSimple::randomParametersChange() {
  // strategy does not have any parameters to change
}

std::string BSimple::getDescription() {
    return "Simplest strategy for buyer. Accepts deal if his gain isn't negative.";
}

StrategyAbstract* BSimple::copy(Player* player) const {
    return (new BSimple(this))->changeOwner(player);
}

std::string BSimple::getName() {
    return "BSimple";
}

BSimple::~BSimple() = default;