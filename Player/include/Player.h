#pragma once

/*
 * Base class with derived classes Buyer and Seller. Operates with vector of strategies
 */

#include <stdexcept>
#include <vector>
#include <algorithm>
#include "../../BasicStrategies/StrategyAbstract.h"

class Player {
public:
    Player() = delete;
    explicit Player(size_t mIG) : movesInGame(mIG) {}; //does not initialise fields that always should initialise at the start of each game from class AuctionGame.

    inline const StrategyAbstract* getCurrentStrategy() const { // Player may have a lot of different strategy he plays, this gives his current strategy
        return strategies[currentStrategy];
    }

    void setPreviousMoves(std::vector<class pmove>*); // Player should know results of all previous moves in game because his strategy (may) depend on it
    static std::vector<Player*> findBestPlayers(int, std::vector<Player*>&); // Find players with highest gain. NOT const, sorts players (their order is not important).

    inline size_t getCurrentMove() const {
        return currentMove;
    }

    inline int getTotalProfit() const {
        return totalProfit;
    }

    inline const std::vector<class pmove>* getPreviousMoves() const {
        return previousMoves;
    }

    void clearProfit(); // clears gain of player
    void newGame(std::vector<pmove>*); // assigns currentMove, currentStrategy and previousMoves at the start of each game.

    virtual void addProfit(int) = 0; // function of gain differs for Buyer and Seller

    struct byProfit { //functor that sorts players by their gain descending
        bool operator () (const Player* a, const Player* b);
    };

protected:
    const size_t movesInGame;
    size_t currentMove; // current move in playing game
    size_t currentStrategy; // number of current strategy player using
    int totalProfit; // gain of player (at the step of genetic cycle)
    std::vector<StrategyAbstract*> strategies; // all strategies player is using
    std::vector<class pmove>* previousMoves;
    void shiftMove(); // increment currentMove and change currentStrategy accordingly
};