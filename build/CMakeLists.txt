cmake_minimum_required(VERSION 3.10)

project(auctionGame)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused-parameter")

include_directories( "../BasicStrategies" )
include_directories( "../MainLogic/include" )
include_directories( "../Player/include" )
include_directories( "../BasicStrategies/Pairing/include" )
include_directories( "../BasicStrategies/BuyerStrategies/include" )
include_directories( "../BasicStrategies/SellerStrategies/include" )
include_directories( "../BasicStrategies/Pairing" )
include_directories( "../BasicStrategies/BuyerStrategies" )
include_directories( "../BasicStrategies/SellerStrategies" )

set (SOURCES ${SOURCES} ../BasicStrategies/generalStates.cpp)
set (SOURCES ${SOURCES} ../BasicStrategies/StrategiesController.cpp)

set (SOURCES ${SOURCES} ../Player/src/Player.cpp)
set (SOURCES ${SOURCES} ../Player/src/Buyer.cpp)
set (SOURCES ${SOURCES} ../Player/src/Seller.cpp)

#Here goes sellers strategies
set (SOURCES ${SOURCES} ../BasicStrategies/SellerStrategies/src/SBinarySearch.cpp)
set (SOURCES ${SOURCES} ../BasicStrategies/SellerStrategies/src/SCompleteRandom.cpp)
#

#Here goes buyers strategies
set (SOURCES ${SOURCES} ../BasicStrategies/BuyerStrategies/src/BSimple.cpp)
set (SOURCES ${SOURCES} ../BasicStrategies/BuyerStrategies/src/BCompleteRandom.cpp)
set (SOURCES ${SOURCES} ../BasicStrategies/BuyerStrategies/src/BIncreaseProfit.cpp)
#

#Here goes pairing functions
set (SOURCES ${SOURCES} ../BasicStrategies/Pairing/src/PSimple.cpp)
set (SOURCES ${SOURCES} ../BasicStrategies/Pairing/src/PSmt.cpp)
#

set (SOURCES ${SOURCES} ../MainLogic/src/AuctionGame.cpp)
set (SOURCES ${SOURCES} ../MainLogic/src/StatisticCollector.cpp)
set (SOURCES ${SOURCES} ../MainLogic/src/GeneticCycle.cpp)

set (SOURCES ${SOURCES} ../MainLogic/src/main.cpp )

add_executable (auctionGame ${SOURCES})
