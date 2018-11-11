#include "../include/Player.h"

/*
 * Base class with derived classes Buyer and Seller. Operates with vector of strategies
 */


/*
 * increment currentMove and change currentStrategy accordingly
 */
void Player::shiftMove() {
    currentMove++;
    if (currentMove > getCurrentStrategy() -> endMove) {
        currentStrategy++;
    }
}

/*
 * Player should know results of all previous moves in game because his strategy (may) depend on it
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
bool Player::byProfit::operator () (const Player* a, const Player* b) {
    return a -> totalProfit > b -> totalProfit;
}

/*
 * clears gain of player
 */
void Player::clearProfit() {
    totalProfit = 0;
}


/*
 * Find players with highest gain. NOT const, sorts players (their order is not important).
 */
std::vector<Player*> Player::findBestPlayers(int numberOfPlayers, std::vector<Player*>& players) {
    if (players.empty()) {
        throw std::runtime_error("findBestPlayers() : empty vector of players");
    }

    sort(players.begin(), players.end(), byProfit());
    std::vector<Player*> bestPlayers;

    for (size_t i = players.size() - 1; numberOfPlayers > 0; --numberOfPlayers, i = (i == 0) ? (players.size() - 1) : (i - 1) ) {
        bestPlayers.push_back(players[i]);
    }

    return bestPlayers;
}
