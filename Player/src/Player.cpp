#include "./player.h"

StrategyAbstract& Player::getCurrentStrategy() {
    return strategies<currentStrategy>;
}

void Player::shiftMove() {
    currentMove++;
    if (currentMove > getCurrentStrategy().endMove) {
        currentStrategy++;
    }
}
