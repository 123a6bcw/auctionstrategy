#pragma once

/*
 * Binary search on buyer profit. Assumes that buyer's profit is between inputMinValue and inputMaxValue.
 * Proposes deal with the average value and change currentMinValue and currentMaxValue accordingly to the result of the deal.
*/

#include "../SellerStrategyAbstract.h"

class SBinarySearch : public SellerStrategyAbstract {
private:
    int inputMaxValue; //assumed maximum possible profit of buyer
    int inputMinValue; //minimum
    int currentMaxValue; //calculated (assumed) possible profit of buyer
    int currentMinValue; //minimum
    explicit SBinarySearch(const SBinarySearch*);
public:
    SBinarySearch(Player*, size_t, size_t);
    int setPrice() override; //for comments on overrided functions see AbstractStrategy and SellerAbstractStrategy
    void reset() override;
    void randomParametersChange() override;
    ~SBinarySearch() override;
    StrategyAbstract* copy(Player*) const override;
};