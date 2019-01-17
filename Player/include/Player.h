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
    RandomNumberGenerator* randomNumberGenerator;

    void setPreviousMoves(const std::vector<class pmove>*); // Player should know results of all previous moves in game because his strategy (may) depend on it
    static std::vector<Player*> findBestPlayers(size_t, std::vector<Player*>*); // Find players with highest gain. NOT const, sorts players (their order is not important).
    void clearGain(); // clears gain of player
    void newGame(const std::vector<pmove>*); // assigns currentMove, currentStrategy and previousMoves at the start of each game.
    std::vector<StrategyAbstract*>* getStrategies() const; //TODO comment
    std::vector<StrategyAbstract*>* copyStrategies(Player*) const; //TODO comment

    virtual void addGain(int) = 0; // function of adding gain differs for Buyer and Seller
    virtual Player* copy() const = 0; //creates copy of this Player and all his strategies.
    virtual ~Player();

    Player() = delete;
protected:
    /*
     * User should always use only either Buyer or Seller constructors
     */
    explicit Player(size_t, int, RandomNumberGenerator*, StrategiesController*, typeOfPlayer);
    explicit Player(size_t, int, RandomNumberGenerator*, StrategiesController*, typeOfPlayer, std::vector<StrategyAbstract*>*);
    explicit Player(size_t movesInGame, RandomNumberGenerator* randomNumberGenerator, StrategiesController* controller, typeOfPlayer type);
    explicit Player(size_t, RandomNumberGenerator*, StrategiesController*, typeOfPlayer, std::vector<StrategyAbstract*>*);

    StrategiesController* controller;

    const size_t movesInGame;
    size_t currentMove; // current move in playing game
    size_t currentStrategy; // number of current strategy player using
    int totalGain; // gain of player at the step of genetic cycle
    std::vector<StrategyAbstract*>* strategies; // all strategies player is using
    const std::vector<class pmove>* previousMoves;
    typeOfPlayer type; //player's type (either SELLER or BUYER)

    void shiftMove(); // increment currentMove and change currentStrategy accordingly

    inline StrategyAbstract* getCurrentStrategy() { // only Player (and derived classes) can use strategy with ability to change it (aka not const)
        return (*strategies)[currentStrategy];
    }
    explicit Player(const Player*); // public interface should use virtual function copy
public:
    /*
     * inline functions
     */
    inline const class StrategyAbstract* getCurrentStrategy() const { // Player may have a lot of different strategy he plays, this gives his current strategy
        return (*strategies)[currentStrategy];
    }

    inline size_t getCurrentMove() const {
        return currentMove;
    }

    inline int getTotalGain() const {
        return totalGain;
    }

    inline const std::vector<class pmove>* getPreviousMoves() const {
        return previousMoves;
    }

    struct byGain { //functor that sorts players by their gain descending
        bool operator () (const Player* a, const Player* b) const;
    };
};