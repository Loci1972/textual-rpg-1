#!/bin/sh
g++ -Wall -Wextra -std=c++11 -I./headers main.cpp src/*.cpp -o build/rpg_game && ./build/rpg_game
