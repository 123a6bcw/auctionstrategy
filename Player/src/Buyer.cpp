bool Buyer::acceptDeal(int price) {
    bool answer = getCurrentStrategy().acceptDeal(price);
    shiftMove();
}
