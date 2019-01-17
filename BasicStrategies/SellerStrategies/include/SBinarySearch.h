#pragma once

/*
 * Binary search on buyer profit. Assumes that buyer's profit is between inputMinValue and inputMaxValue.
 * Proposes deal with the average value and change currentMinValue and currentMaxValue accordingly to the result of the deal.
*/

#include "../SellerStrategyAbstract.h"

class SBinarySearch : public SellerStrategyAbstract {
private:
    int inputMinValue; //assumed minimum possible profit of buyer
    int inputMaxValue; //maximum
    int currentMaxValue; //calculated (assumed) possible profit of buyer
    int currentMinValue; //minimum
    explicit SBinarySearch(const SBinarySearch*);
public:
    SBinarySearch(Player*, size_t, size_t, int, int);
    StrategyAbstract* copy(Player*) const override;
    void reset() override;
    int setPrice() override; //for comments on overrided functions see AbstractStrategy and SellerAbstractStrategy
    void randomParametersChange() override;
    ~SBinarySearch() override;
    std::string getName() override;
    std::string getDescription() override;
};