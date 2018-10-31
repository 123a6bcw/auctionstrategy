#include "../include/AuctionGame.h"

int main(int argc, char* argv[]) {
    Pairing::Seller::PSimple pairBuyers;
    Pairing::Buyer::PSimple pairSellers;
    AuctionGame(int(argv[0]), int(argv[1]), int(argv[2]), int(argv[3]), pairBuyers, pairSellers);
}
