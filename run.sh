#!/bin/bash

clear 

g++ src/main.cpp src/game.cpp src/fish.cpp src/shark.cpp src/animal.cpp src/random.cpp -o run

# run the program if compiled
if [ -f run ]
then
    ./run
fi

