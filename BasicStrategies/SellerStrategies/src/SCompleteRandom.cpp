/*
 * Template for creating sellers's strategy.
 * INSTRUCTION
 1. Create header file with desired name.                           +
 2. Only change NAMEOFSTRATEGY in header file
      (or add. functions and parameters), (check name conflicts!)   +
 3. Change #include "../include/???.h" according to header          +
 4. Define NAMEOFSTRATEGY in this file according to header file     +
 5. Implement all listed function                                   +
 6. include created header file to AllSellerStrategies.h            +
 7. in StrategiesController.h increment numberOfSellerStrategies    +
 8. in StrategiesController.cpp in function createSellerStrategy:
       * add case with consectuive number                           +
       * implement calling constructor for creating strategy with   +
           default (random) parameters
 9. add this cpp file to CMakeLists.txt                             +
 */

#include "../include/SCompleteRandom.h"
#include <iostream>
#include "../../../Player/include/Player.h"

#ifndef TOSTRING
#define STR(x) #x
#define TOSTRING(x) STR(x)
#endif

#define NAMEOFSTRATEGY SCompleteRandom

/*
* Constructor.
*/
NAMEOFSTRATEGY::NAMEOFSTRATEGY(Player* p, size_t _startMove, size_t _endMove, int _minValue, int _maxValue) : SellerStrategyAbstract(p, _startMove, _endMove),
  minValue(_minValue), maxValue(_maxValue) {}

/*
* Copying;
*/
NAMEOFSTRATEGY::NAMEOFSTRATEGY(const NAMEOFSTRATEGY* sbs) : SellerStrategyAbstract(sbs), minValue(sbs->minValue), maxValue(sbs->maxValue) {}

/*
* Set changing fields during playing one game to it's default values
* No parameteres need to reset
 */
void NAMEOFSTRATEGY::reset() {
}

/*
* Propose a deal to buyer.
*/
int NAMEOFSTRATEGY::setPrice() {
    return owner->randomNumberGenerator->getRandomNumber(minValue, maxValue);
}

/*
* Short description what does this strategy doing.
*/
std::string NAMEOFSTRATEGY::getDescription() {
    return "Propose absolutely random deal in given range";
}

/*
* Not quite sure yet that this function supposed to be doing. Something like slightly changing the parameters for genetic diversity.
* TODO: implement?
*/
void NAMEOFSTRATEGY::randomParametersChange() {
}

/*
* Descructor. Implement if neccessary
*/
NAMEOFSTRATEGY::~NAMEOFSTRATEGY() = default;

/*
* DON"T CHANGE
* Copying with changing owner
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
