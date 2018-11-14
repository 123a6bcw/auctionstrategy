#include "../include/SBinarySearch.h"

/*
 * Binary search on buyer profit. Assumes that buyer's profit is between minValue and maxValue.
 * Proposes deal with the average value and change minValue and maxValue accordingly to the result of the deal.
*/

#include <iostream>

SBinarySearch::SBinarySearch(Player* p, size_t _startMove, size_t _endMove) : SellerStrategyAbstract(p, _startMove, _endMove) {
    inputMaxValue = rand() % 1000 + 5;
    inputMinValue = rand() % (inputMaxValue - 1);
    std::cout << inputMaxValue << " " << inputMinValue << std::endl;
    //TODO bad way to assume inputMinValue and inputMaxValue
}

SBinarySearch::SBinarySearch(const SBinarySearch* sbs) : SellerStrategyAbstract(sbs),inputMaxValue(sbs -> inputMaxValue), inputMinValue(sbs -> inputMinValue) {}

StrategyAbstract* SBinarySearch::copy(Player* player) const {
    auto copyStrategy = new SBinarySearch(this);
    copyStrategy -> owner = player;
    return copyStrategy;
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
