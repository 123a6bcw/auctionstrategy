cmake_minimum_required(VERSION 3.10)

project(auctionGame)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused-parameter")

include_directories( "../BasicStrategies" )
include_directories( "../MainLogic/include" )
include_directories( "../Player/include" )
include_directories( "../BasicStrategies/Pairing/include" )
include_directories( "../BasicStrategies/BuyerStrategies/include" )
include_directories( "../BasicStrategies/SellerStrategies/include" )
include_directories( "../BasicStrategies/Pairing" )
include_directories( "../BasicStrategies/BuyerStrategies" )
include_directories( "../BasicStrategies/SellerStrategies" )

set (SOURCES ${SOURCES} ../BasicStrategies/generalStates.cpp ../BasicStrategies/generalStates.h)
set (SOURCES ${SOURCES} ../BasicStrategies/StrategiesController.cpp ../BasicStrategies/StrategiesController.h)

set (SOURCES ${SOURCES} ../Player/src/Player.cpp ../Player/include/Player.h)
set (SOURCES ${SOURCES} ../Player/src/Buyer.cpp ../Player/include/Buyer.h)
set (SOURCES ${SOURCES} ../Player/src/Seller.cpp ../Player/include/Seller.h)

#Here goes sellers strategies
set (SOURCES ${SOURCES} ../BasicStrategies/SellerStrategies/src/SBinarySearch.cpp ../BasicStrategies/SellerStrategies/include/SBinarySearch.h)
set (SOURCES ${SOURCES} ../BasicStrategies/SellerStrategies/src/SCompleteRandom.cpp ../BasicStrategies/SellerStrategies/include/SCompleteRandom.h)
#

#Here goes buyers strategies
set (SOURCES ${SOURCES} ../BasicStrategies/BuyerStrategies/src/BSimple.cpp ../BasicStrategies/BuyerStrategies/include/BSimple.h)
set (SOURCES ${SOURCES} ../BasicStrategies/BuyerStrategies/src/BCompleteRandom.cpp ../BasicStrategies/BuyerStrategies/include/BCompleteRandom.h)
set (SOURCES ${SOURCES} ../BasicStrategies/BuyerStrategies/src/BIncreaseProfit.cpp ../BasicStrategies/BuyerStrategies/include/BIncreaseProfit.h)
#

#Here goes pairing functions
set (SOURCES ${SOURCES} ../BasicStrategies/Pairing/src/PSimple.cpp ../BasicStrategies/Pairing/include/PSimple.h)
set (SOURCES ${SOURCES} ../BasicStrategies/Pairing/src/PSmt.cpp ../BasicStrategies/Pairing/include/PSmt.h)
#

set (SOURCES ${SOURCES} ../MainLogic/src/AuctionGame.cpp ../MainLogic/include/AuctionGame.h)
set (SOURCES ${SOURCES} ../MainLogic/src/StatisticCollector.cpp ../MainLogic/include/StatisticCollector.h)
set (SOURCES ${SOURCES} ../MainLogic/src/GeneticCycle.cpp ../MainLogic/include/GeneticCycle.h)
set (SOURCES ${SOURCES} ../MainLogic/src/PartedGeneticCycle.cpp ../MainLogic/include/PartedGeneticCycle.h)
set (SOURCES ${SOURCES} ../MainLogic/src/PlayersHandler.cpp ../MainLogic/include/PlayersHandler.h)

set (SOURCES ${SOURCES} ../MainLogic/src/main.cpp)
add_executable (auctionGame ${SOURCES})
