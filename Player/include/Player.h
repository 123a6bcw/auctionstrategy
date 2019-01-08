#pragma once

/*
 * Base class with derived classes Buyer and Seller. Operates with vector of strategies
 */

#include <stdexcept>
#include <vector>
#include <algorithm>
#include "../../BasicStrategies/StrategiesController.h"
#include "../../BasicStrategies/generalStates.h"
#include "../../BasicStrategies/StrategyAbstract.h"

class Player {
    friend class StrategyAbstract;
public:
    Player() = delete;

    explicit Player(size_t mIG, int profit, RandomNumberGenerator* rng, StrategiesController* controller, typeOfPlayer type);

    inline const class StrategyAbstract* getCurrentStrategy() const { // Player may have a lot of different strategy he plays, this gives his current strategy
        return (*strategies)[currentStrategy];
    }

    void setPreviousMoves(const std::vector<class pmove>*); // Player should know results of all previous moves in game because his strategy (may) depend on it
    static std::vector<Player*> findBestPlayers(size_t, std::vector<Player*>*); // Find players with highest gain. NOT const, sorts players (their order is not important).

    inline size_t getCurrentMove() const {
        return currentMove;
    }

    inline int getTotalGain() const {
        return totalGain;
    }

    inline const std::vector<class pmove>* getPreviousMoves() const {
        return previousMoves;
    }

    void clearGain(); // clears gain of player
    void newGame(const std::vector<pmove>*); // assigns currentMove, currentStrategy and previousMoves at the start of each game.

    virtual void addGain(int) = 0; // function of adding gain differs for Buyer and Seller

    struct byGain { //functor that sorts players by their gain descending
        bool operator () (const Player* a, const Player* b) const;
    };

    RandomNumberGenerator* randomNumberGenerator;
    virtual Player* copy() const = 0; //creates copy of this Player and all his strategies.
    std::vector<StrategyAbstract*>* copyStrategies(Player*) const;
    virtual ~Player();
    std::vector<StrategyAbstract*>* getStrategies() const;
protected:
    const size_t movesInGame;
    size_t currentMove; // current move in playing game
    size_t currentStrategy; // number of current strategy player using
    int totalGain; // gain of player at the step of genetic cycle
    std::vector<StrategyAbstract*>* strategies; // all strategies player is using
    const std::vector<class pmove>* previousMoves;
    StrategiesController* controller;
    typeOfPlayer type; //player's type (either SELLER or BUYER)
    void shiftMove(); // increment currentMove and change currentStrategy accordingly

    inline StrategyAbstract* getCurrentStrategy() { // only Player (and derived classes) can use strategy with ability to change it (aka not const)
        return (*strategies)[currentStrategy];
    }

    explicit Player(const Player*); // public interface should use virtual function copy
};