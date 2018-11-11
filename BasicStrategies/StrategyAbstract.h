#pragma once

#include <vector>
#include "../Player/include/Player.h"
#include "./generalStates.h"

class StrategyAbstract {
    friend class Player;
public:
    StrategyAbstract(class Player* p, size_t sM, size_t eM) : owner(p), startMove(sM), endMove(eM) {};
    virtual void randomParametersChange() = 0;

protected:
    Player* owner;
    size_t startMove;
    size_t endMove;
};
