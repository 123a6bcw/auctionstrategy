#!/bin/bash

#this changes compile flags from local version with a lot of warnings to relise version without them

cat "../CMakeLists.txt" | sed "s/set (CMAKE_CXX_FLAGS \"\${CMAKE_CXX_FLAGS} -pthread -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused\")/set (CMAKE_CXX_FLAGS \"\${CMAKE_CXX_FLAGS} -pthread\")/" > "CMakeLists.txt"

sudo cmake CMakeLists.txt
make
mkdir ../logs
mkdir ../logs/transformed
