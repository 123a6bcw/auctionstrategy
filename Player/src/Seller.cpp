#include "../include/Seller.h"

Seller::Seller(size_t mIG) : Player(mIG) {
    currentMove = 0;
    currentStrategy = 0;
    totalProfit = 0;
    strategies = std::vector<StrategyAbstract*>(0);
    strategies.push_back(new SBinarySearch(this, 0, movesInGame - 1));
}

int Seller::setPrice() {
    int answer = (dynamic_cast<SellerStrategyAbstract*>(getCurrentStrategy())) -> setPrice();
    shiftMove();
    return answer;
}

void Seller::addProfit(int price) {
    totalProfit += price;
}
