//TODO: comment

#include "../include/PartedGeneticCycle.h"

PartedGeneticCycle::PartedGeneticCycle(size_t numberOfSellers, size_t numberOfBuyers, size_t ptrNumber, PlayersHandler* playersHandler, size_t movesInGame) :
    playersHandler(playersHandler),
    sellersParts(std::vector< std::pair<size_t, size_t>>(0)),
    buyersParts(std::vector< std::pair<size_t, size_t>>(0)),
    moves(std::vector<std::vector<std::vector<pmove>>>(numberOfSellers, std::vector<std::vector<pmove>>(numberOfBuyers, std::vector<pmove>(0)))),
    movesInGame(movesInGame)
    {
    if (numberOfBuyers < ptrNumber || numberOfSellers < ptrNumber) {
        throw(std::runtime_error("Genetic Cycle: number of buyers or sellers should be at least 10"));
    }

    createPartition(numberOfSellers, ptrNumber, &sellersParts);
    createPartition(numberOfBuyers, ptrNumber, &buyersParts);
}

/*
 * Creates partition: split players with number from 1 to "numberOfPlayers" into "partsNumber" equal (possibly except the last one) parts,
 * store in vector "parts" beginning and ending of each part: players in range [start, end) -> pair(start, end).
 */
void PartedGeneticCycle::createPartition(size_t numberOfPlayers, size_t partsNumber, std::vector<std::pair<size_t, size_t>>* parts) {
    size_t playersInPart = numberOfPlayers / partsNumber;
    size_t startPlayer = 0;
    for (size_t i = 0; i < partsNumber; i++) {
        size_t endPlayer = startPlayer + playersInPart;
        if (i + 1 == partsNumber) {
            endPlayer = numberOfPlayers; // last part can be larger if (numberOfPlayers `mod` partsNumber != 0)
        }

        parts->push_back({startPlayer, endPlayer});
        startPlayer += playersInPart;
    }
}

/*
 * each player in given parts plays with each other. That way we can parallel this process
 */
void PartedGeneticCycle::runPartedCycle(size_t sellerPart, size_t buyerPart) {
    AuctionGame game;

    for (size_t s = sellersParts[sellerPart].first; s < sellersParts[sellerPart].second; s++) {
        for (size_t b = buyersParts[buyerPart].first; b < buyersParts[buyerPart].second; b++) {
            game(playersHandler->getSeller(s), playersHandler->getBuyer(b), movesInGame, &moves[s][b]);
        }
    }
}
