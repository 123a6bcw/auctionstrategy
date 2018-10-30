cmake_minimum_required(VERSION 3.10)

project(auctionStrategy)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories( "../include" )
include_directories( "../Player" )
include_directories( "../BasicStrategies" )

set (SOURCES "../src/main.cpp")
set (SOURCES "")

add_executable (main ${SOURCES})
