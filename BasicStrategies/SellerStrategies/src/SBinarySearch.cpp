#include "../include/SBinarySearch.h"

/*
 * Binary search on buyer profit. Assumes that buyer's profit is between minValue and maxValue.
 * Proposes deal with the average value and change minValue and maxValue accordingly to the result of the deal.
*/

#include <iostream>
#include "../../../Player/include/Player.h"

SBinarySearch::SBinarySearch(Player* player, size_t startMove, size_t endMove, int inputMinValue, int inputMaxValue):
SellerStrategyAbstract(player, startMove, endMove),
inputMinValue(inputMinValue),
inputMaxValue(inputMaxValue)
{
}

SBinarySearch::SBinarySearch(const SBinarySearch* sBinarySearch):
SellerStrategyAbstract(sBinarySearch),
inputMinValue(sBinarySearch -> inputMinValue),
inputMaxValue(sBinarySearch -> inputMaxValue)
{}

StrategyAbstract* SBinarySearch::copy(Player* player) const {
    return (new SBinarySearch(this))->changeOwner(player);
}

void SBinarySearch::reset() {
    currentMinValue = inputMinValue;
    currentMaxValue = inputMaxValue;
}

int SBinarySearch :: setPrice() {
    if (owner -> getCurrentMove() > startMove) {
        // It's not the first time strategy is used. We need to change current min and max values accordingly to the result of previous deal
        int middle = getMiddle(currentMinValue, currentMaxValue);
        const pmove& lastMove = owner -> getPreviousMoves() -> back();
        if (lastMove.wasSold()) {
            currentMinValue = middle - 1; //currentMinValue is always smaller than smallest possible buyer's profit, (maxValue - minValue) >= 2 in order to always have correct middle
        } else {
            currentMaxValue = middle + 1;
        }
    }

    return getMiddle(currentMinValue, currentMaxValue);
}

void SBinarySearch::randomParametersChange() {
    // TODO
}

SBinarySearch::~SBinarySearch() = default;

std::string SBinarySearch::getName() {
    return "SBinarySearch";
}

std::string SBinarySearch::getDescription() {
    return "Binary search on buyer profit."
           "Assumes that buyer's profit is between minValue and maxValue."
           "Proposes deal with the average value and change minValue"
           "and maxValue accordingly to the result of the deal.";
}
