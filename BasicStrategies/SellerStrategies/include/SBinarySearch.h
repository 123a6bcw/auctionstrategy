#pragma once

#include "../SellerStrategyAbstract.h"

class SBinarySearch : public SellerStrategyAbstract {
private:
    int maxValue;
    int minValue;
public:
    SBinarySearch(Player* p, size_t _startMove, size_t _endMove) : SellerStrategyAbstract(p, _startMove, _endMove) {};
    int setPrice() override;
    void randomParametersChange() override;
};