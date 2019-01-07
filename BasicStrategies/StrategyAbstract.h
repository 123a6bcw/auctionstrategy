#pragma once

/*
 * Abstract class for strategies of Player. Derived classes are BuyerStrategyAbstract and SellerStrategyAbstract
 */

#include <vector>
#include "./generalStates.h"

class Player;

class StrategyAbstract {
    friend class Player;
public:
    StrategyAbstract() = delete;
    StrategyAbstract(class Player* p, size_t sM, size_t eM) : owner(p), startMove(sM), endMove(eM) {};
    virtual void randomParametersChange() = 0; // slightly randomly changes parameters of strategy in order of improving genetic cycle.
    virtual void reset() = 0; // each strategy may calculate some additional parameters during it's usage. This resetting this parameters when strategy using in game for the first time.
    virtual StrategyAbstract* copy(Player*) const = 0; //creates copy of this strategy with new owner
    virtual std::string getName() = 0;
    virtual std::string getDescription() = 0;
    virtual ~StrategyAbstract() = default;
    inline size_t getMovesLength() {
        return endMove - startMove + 1;
    }
    inline StrategyAbstract* changeOwner(Player* player) {
        owner = player;
        return this;
    }
protected:
    Player* owner; /* Player who uses this strategy. For now only uses his vector of previous moves cause strategy (may) depend on it.
                   * vector of previous moves does not throws to each strategy in order of optimization --- otherwise we had to initialise it at the begining of each game for each strategy.
                   */
    size_t startMove; //game has moves with numbers [0, movesInGame - 1). This shows moves that will use this strategy
    size_t endMove; // strategy plays in moves [startMove, endMove]. Inclusive!!!
    explicit StrategyAbstract(const StrategyAbstract* sa) : owner(sa -> owner), startMove(sa -> startMove), endMove(sa -> endMove) {}; //protected, because public interface uses virtual copy()
};
