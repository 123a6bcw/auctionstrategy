#include "../include/Buyer.h"

Buyer::Buyer(size_t mIG, int _profit) : Player(mIG), profit(_profit) {
    //TODO

    if (mIG == 0) {
        //VERY BAD THROW EXCEPTION
    }

    currentMove = 0;
    currentStrategy = 0;
    totalProfit = 0;
    strategies = std::vector<StrategyAbstract*>(0);
    strategies.push_back(new BSimple(this, 0, movesInGame - 1, profit));
}

bool Buyer::acceptDeal(int price) {
    bool answer = dynamic_cast<Buyer*>(getCurrentStrategy()) -> acceptDeal(price);
    shiftMove();
    return answer;
}

void Buyer::addProfit(int price) {
    totalProfit += profit - price;
}