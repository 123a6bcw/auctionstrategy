#include "../include/BIncreaseProfit.h"
#include "../../../Player/include/Player.h"

#define NAMEOFSTRATEGY BIncreaseProfit

#ifndef TOSTRING
#define STR(x) #x
#define TOSTRING(x) STR(x)
#endif

/*
* Constuctor. Some additional parameteres may required
*/
NAMEOFSTRATEGY::NAMEOFSTRATEGY(Player* player, size_t startMove, size_t endMove, int profit, int falseProfit, size_t pretendMovesLength) :
BuyerStrategyAbstract(player, startMove, endMove, profit),
falseProfit(falseProfit),
pretendMovesLength(pretendMovesLength)
{
    pretendMovesLeft = pretendMovesLength;
}

/*
* Copying
*/
NAMEOFSTRATEGY::NAMEOFSTRATEGY(const NAMEOFSTRATEGY* anotherStrategy):
BuyerStrategyAbstract(anotherStrategy),
falseProfit(anotherStrategy->falseProfit),
pretendMovesLength(anotherStrategy->pretendMovesLength),
pretendMovesLeft(anotherStrategy->pretendMovesLeft)
{
}

/*
* Set changing fields during playing one game to it's default values
*/
void NAMEOFSTRATEGY::reset() {
    pretendMovesLeft = pretendMovesLength;
}

/*
* Function that either accept deal proposed by seller or not
*/
bool NAMEOFSTRATEGY::acceptDeal(int price) {
    if (pretendMovesLeft-- > 0) {
        return price < falseProfit;
    }

    return price < profit;
}

/*
* Short description what does this strategy doing.
*/
std::string NAMEOFSTRATEGY::getDescription() {
    return "Plays simple strategy, but for given number of moves pretends his profit is falseProfit where falseProfit > profit";
}

/*
* Not quite sure yet that this function supposed to be doing. Something like slightly changing the parameters for genetic diversity.
* TODO: Implement, comments
*/
void NAMEOFSTRATEGY::randomParametersChange() {
    // idk yet that to write
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
    return TOSTRING(NAMEOFSTRATEGY);
}

#undef NAMEOFSTRATEGY
