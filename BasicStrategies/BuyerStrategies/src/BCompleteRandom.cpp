#include "../include/BCompleteRandom.h"
#include "../../../Player/include/Player.h"

#define NAMEOFSTRATEGY BCompleteRandom

NAMEOFSTRATEGY::NAMEOFSTRATEGY(Player* player, size_t startMove, size_t endMove, int profit):
BuyerStrategyAbstract(player, startMove, endMove, profit)
{
}

/*
* Copying 
* There is no parameters in this strategy
*/
NAMEOFSTRATEGY::NAMEOFSTRATEGY(const NAMEOFSTRATEGY* anotherStrategy) : BuyerStrategyAbstract(anotherStrategy) {
}

/*
* Set changing fields during playing one game to it's default values
* No parameters to reset
*/
void NAMEOFSTRATEGY::reset() {
}

/*
* Function that either accept deal proposed by seller or not
* Completely random decision.
*/
bool NAMEOFSTRATEGY::acceptDeal(int price) {
    (void)price;
    return static_cast<bool>(owner->randomNumberGenerator->getRandomNumber(0, 1));
}

/*
* Not quite sure yet that this function supposed to be doing. Something like slightly changing the parameters for genetic diversity.
* No parameters to change
*/
void NAMEOFSTRATEGY::randomParametersChange() {
}

/*
* Short description what does this strategy doing.
*/
std::string NAMEOFSTRATEGY::getDescription() {
    return "Completely random strategy";
}

/*
* Descructor. Implement if necessary
*/
NAMEOFSTRATEGY::~NAMEOFSTRATEGY() = default;

/*
* DON'T CHANGE
* Copy strategy with changing owner of strategy.
*/
StrategyAbstract* NAMEOFSTRATEGY::copy(Player* player) const {
    return (new NAMEOFSTRATEGY(this))->changeOwner(player);
}

/*
* DON"T CHANGE
* Returns the name of this class 
*/
std::string NAMEOFSTRATEGY::getName() {
    return "BCompleteRandom";
}

#undef NAMEOFSTRATEGY
