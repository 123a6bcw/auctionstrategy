#include "../include/Player.h"

/*
 * Base class with derived classes Buyer and Seller. Operates with vector of strategies
 */

Player::Player(const Player* p) : movesInGame(p -> movesInGame) {}

/*
 * increment currentMove and change currentStrategy accordingly
 */
void Player::shiftMove() {
    currentMove++;
    if (currentMove > getCurrentStrategy() -> endMove) {
        currentStrategy++;
        if (currentMove < movesInGame && currentStrategy >= strategies.size()) {
            throw std::runtime_error("shiftMove() : Player has run out of strategies to use.");
        }
        getCurrentStrategy() -> reset(); //each strategy may calculate some parameters during it's usage, so we need to reset them before using for the first time.
    }
}

/*
 * Player should know results of all previous moves in game because his strategies (may) depend on it
 */
void Player::setPreviousMoves(std::vector<pmove>* t) {
    previousMoves = t;
}

/*
 * assigns currentMove, currentStrategy and previousMoves at the start of each game.
 */
void Player::newGame(std::vector<pmove>* _previousMoves) {
    setPreviousMoves(_previousMoves);
    currentMove = 0;
    currentStrategy = 0;
}

/*
 * functor that sorts players by their gain descending
 */
bool Player::byGain::operator () (const Player* a, const Player* b) const {
    return a -> totalGain > b -> totalGain;
}

/*
 * clears gain of player
 */
void Player::clearGain() {
    totalGain = 0;
}

std::vector<StrategyAbstract*> Player::copyStrategies(Player* newPlayer) const {
    std::vector<StrategyAbstract*> copied;
    for (auto x : strategies) {
        copied.push_back(x -> copy(newPlayer));
    }

    return copied;
}


/*
 * Find players with highest gain. Changes (sorts) given vector of players (their order is not important so that's ok).
 */
std::vector<Player*> Player::findBestPlayers(size_t numberOfPlayers, std::vector<Player*>& players) {
    if (players.empty()) {
        throw std::runtime_error("findBestPlayers() : empty vector of players");
    }
    if (numberOfPlayers > players.size()) {
        throw std::runtime_error("findBestPlayers() : number of players to find is larger than amount of players");
    }

    sort(players.begin(), players.end(), byGain());
    std::vector<Player*> bestPlayers;

    for (size_t i = players.size() - 1; numberOfPlayers > 0; --numberOfPlayers, --i ) {
        bestPlayers.push_back(players[i]);
    }

    return bestPlayers;
}