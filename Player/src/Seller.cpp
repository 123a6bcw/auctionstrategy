int Seller::setPrice() {
    int answer = getCurrentStrategy().setPrice();
    shiftMove();
    return answer;
}

void Seller::addProfit(int price) {
    totalProfit += price;
}
