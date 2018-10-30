#pragma once

#include "../SellerStrategyAbstract.h"

class SBinarySearch : SellerStrategyAbstract {
private:
    int maxValue;
    int minValue;
    int currentMove;
public:
    SBinarySearch(int _endMove, vector&<pmove> prevMoves);
    int setPrice();
};
