bool Buyer::acceptDeal(int price) {
    bool answer = getCurrentStrategy().acceptDeal(price);
    shiftMove();
    return answer;
}

void Buyer::addProfit(int price) {
    totalProfit += profit - price;
}
