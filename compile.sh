#!/bin/sh
g++ -Wall -Wextra -std=c++11 -I./headers main.cpp src/*.cpp -o out/rpg_game && ./out/rpg_game
