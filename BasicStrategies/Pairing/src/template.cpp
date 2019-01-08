/*
* Template for creating new pairing function.
* Instruction:
 1. Create header file with desired name.                          -
 2. Only change NAMEOFPAIRING in header file                       - 
        (check name conflicts!)
 3. Change #include "../include/???.h" according to the header     -
 4. Define NAMEOFPAIRING in this file according to header file     -
 5. Implement operator ()                                          -
 6. include created header file to AllPairing.h                    -
 7. in StrategiesController.cpp in function createSellerPairing:   -
       * add case with consectuive number
       * implement calling constructor for creating pairing with
            (possible) default (random) parameters
 8. add this cpp file to CMakeLists.txt                            -
*/

#include "../include/???.h"
#define NAMEOFPAIRING ???

/*
* creating new players in number of numberOfChildrens
* TODO: implement, comments
*/
void NAMEOFPAIRING::operator () (size_t numberOfChildrens, std::vector<Player*>* players) {
    std::vector<Player*> newChilds = Player::findBestPlayers(numberOfChildrens, players);
    for (auto x : newChilds) {
        players -> push_back(x -> copy());
    }
}

/*
 * desctructor. Implement if neccessary
 */
NAMEOFPAIRING::~NAMEOFPAIRING() = default;

#undef NAMEOFPAIRING
