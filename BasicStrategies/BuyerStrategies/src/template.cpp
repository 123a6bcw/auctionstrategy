/*
 * Template for creating buyer's strategy.
 * INSTRUCTION
 1. Create header file with desired name.                           -
 2. Only change NAMEOFSTRATEGY in header file                       -
         (check name conflicts!)
 3. Change #include "../include/???.h" to according filename        -
 4. Define NAMEOFSTRATEGY in this file according to header file     -
 5. Implement all listed function                                   -
 6. include created header file to AllBuyerStrategies.h             -
 7. in StrategiesController.h increment numberOfBuyerStrategies     -
 8. in StrategiesController.cpp in function createBuyerStrategy:
       * add case with consectuive number                           -
       * implement calling constructor for creating strategy with   -
           default (random) parameters
 9. add this cpp file to CMakeLists.txt                             -
 10. delete this list                                               -
 */

#include "../include/???.h" //sorry, couldn't make define works for include
#include "../../../Player/include/Player.h"

#define NAMEOFSTRATEGY ???

#ifndef TOSTRING
#define STR(x) #x
#define TOSTRING(x) STR(x)
#endif

/*
* Constuctor. Some additional parameteres may required
* TODO: Implement.
*/
NAMEOFSTRATEGY::NAMEOFSTRATEGY(Player* player, size_t startMove, size_t endMove, int profit):
BuyerStrategyAbstract(player, startMove, endMove, profit)
{
}

/*
* Copying
* TODO: Implement
*/
NAMEOFSTRATEGY::NAMEOFSTRATEGY(const NAMEOFSTRATEGY* anotherStrategy):
BuyerStrategyAbstract(anotherStrategy) {
}

/*
* Set changing fields during playing one game to it's default values
* TODO: Implement, comments
*/
void NAMEOFSTRATEGY::reset() {
}

/*
* Function that either accept deal proposed by seller or not
* TODO: Implement, comments
*/
bool NAMEOFSTRATEGY::acceptDeal(int price) {
    return false;
}

/*
* Short description what does this strategy doing.
* TODO: Implement
*/
std::string NAMEOFSTRATEGY::getDescription() {
return "";
}

/*
* Not quite sure yet that this function supposed to be doing. Something like slightly changing the parameters for genetic diversity.
* TODO: Implement, comments
*/
void NAMEOFSTRATEGY::randomParametersChange() {
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
