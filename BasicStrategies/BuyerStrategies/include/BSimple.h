#pragma once

#include "../BuyerStrategyAbstract.h"

class BSimple:BuyerStrategyAbstract {
public:
     BSimple(int _profit, int _endMove, vector<pmove> _prevMoves) : BuyerStrategyAbstract(_profit, _endMove, _prevMoves) {};
}
