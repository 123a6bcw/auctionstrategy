#pragma once

#include "../SellerStrategyAbstract.h"

class SBinarySearch : SellerStrategyAbstract {
private:
    int maxValue;
    int minValue;
public:
    SBinarySearch(int _endMove, vector&<pmove> prevMoves): SellerStrategyAbstract(_endMove, prevMoves);
    int setPrice();
};
