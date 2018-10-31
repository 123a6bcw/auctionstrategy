#include "../include/geneticCycle.h"

GeneticCycle:GeneticCycle(int n, int m, int _totalSteps, int _movesInGame, int _howMuchToKill, BuyerPairingAbstract& pb, SellerPairingAbstract& ps) : 
    totalSteps(_totalSteps), movesInGame(_movesInGame), howMuchToKill(_howMuchToKill) , pairBuyers(pb), pairSellers(ps) {
        buyers = new vector<Buyer>(n);
        sellers = new vector<Seller>(m);
    }

void cycle() {
    play = new AuctionGame(new vector<pmove>);
    stats = new StatisticCounter();
    
    for (int t = 1; t <= totalSteps; t++) {
        clearProfit();
        
        stats.clear();
        
        for (auto x : buyers) {
            stats.gather(x);
        }
        
        for (auto y : sellers) {
            stats.gather(y);
        }
        
        for (auto x : buyers) {
            for (auto y : sellers) {
               const vector<pmove>& moves = play(x, y, movesInGame).returnAllMoves();
               stats.gather(moves);               
            }
        }
        
        destroyWorstPlayers(buyers, howMuchToKill);
        destroyWorstPlayers(sellers, howMuchToKill);
        
        pairBuyers(buyers, howMuchToKill);
        pairSellers(sellers, howMuchToKill);
        
        stats.print();
    }
}
