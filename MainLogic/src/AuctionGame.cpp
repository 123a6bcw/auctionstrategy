#include "../include/AuctionGame.h"

AuctionGame::AuctionGame(Buyer& a, Seller& b, int pl) : buyer(a), seller(b), totalMoves(pl) {};

void operator AuctionGame::() (Buyer& buyer, Seller& seller, int totalMoves) {
    allMoves.clear();
    buyer.setPreviousMoves(allMoves);
    seller.setPreviousMoves(allMoves);
    
    for (int i = 0; i < totalMoves; i++) {
        int price = seller.setPrice();
        bool result = buyer.acceptDeal(price);
        allMoves.push_back({price, result});
        
        if (result) {
            seller.addProfit(price);
            buyer.addProfit(price);
        }
    }
}

vector<pmove> AuctionGame:returnAllMoves() const {
    return vector<pmove>;
}
