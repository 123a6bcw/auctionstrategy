/*
 * Template for creating buyer's strategy.
 * INSTRUCTION
 1. Create header file with desired name.                           +
 2. Only change NAMEOFSTRATEGY in header file                       +
         (check name conflicts!)
 3. Change #include "../include/???.h" to according filename        +
 4. Define NAMEOFSTRATEGY in this file according to header file     +
 5. Implement all listed function                                   -
 6. include created header file to AllBuyerStrategies.h             -
 7. in StrategiesController.h increment numberOfBuyerStrategies     -
 8. in StrategiesController.cpp in function createBuyerStrategy:    -
       * add case with consectuive number 
       * implement calling constructor for creating strategy with 
           default (random) parameters
 9. add this cpp file to CMakeLists.txt                             -
 */

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
NAMEOFSTRATEGY :: NAMEOFSTRATEGY(Player* p, size_t _startMove, size_t _endMove, int _profit, int _falseProfit, size_t _pretendMovesLength) :
              BuyerStrategyAbstract(p, _startMove, _endMove, _profit), falseProfit(_falseProfit), pretendMovesLength(_pretendMovesLength) {
    pretendMovesLeft = pretendMovesLength;
}

/*
* Copying
*/
NAMEOFSTRATEGY :: NAMEOFSTRATEGY(const NAMEOFSTRATEGY* bs) : BuyerStrategyAbstract(bs), falseProfit(bs->falseProfit), pretendMovesLength(bs->pretendMovesLength) {
    pretendMovesLeft = bs->pretendMovesLeft;
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
* Not quite sure yet that this function supposed to be doing. Something like slightly changing the parameters for genetic diversity.
* TODO: Implement, comments
*/
void NAMEOFSTRATEGY::randomParametersChange() {
    // idk yet that to write
}

/*
* Short description what does this strategy doing.
*/
std::string NAMEOFSTRATEGY::getDescription() {
    return "Plays simple strategy, but for given number of moves pretends his profit is falseProfit where falseProfit > profit";
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
