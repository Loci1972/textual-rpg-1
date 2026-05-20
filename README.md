# Textual RPG (C++)


A turn-based RPG that runs in the terminal. Built from scratch in C++ as a personal project to learn systems programming and OOP.

-----
## What it is

You fight enemies, gain XP, level up, and your progress saves between sessions. Nothing fancy — just a combat loop with some depth to it.

-----
## Features

- Turn-based combat

- XP and level progression

- Health, attack, and defense stats

- Dialogue that changes based on your HP

- File-based save system

- Multiple game states (combat, victory, defeat, flee)

-----
## Technical stuff

- OOP with `Player`, `Enemy`, and `Game` classes

- Split across `.h` / `.cpp` files

- File I/O with `std::fstream`

- Enum-driven game state logic

-----
## Project structure

```
.


├── main.cpp


├── player.h / player.cpp


├── enemy.h / enemy.cpp


├── game.h / game.cpp


├── tools.h / tools.cpp


├── item.h / item.cpp


```
-----
## Build & run

```bash
clang++ -std=c++11 main.cpp src/*.cpp -o rpg_game
./rpg_game


```

-----
## Save system

Saves to `save.txt` — stores name, level, XP, stats, and gold.

-----
## What’s next


- Shop system


- Special attacks


- Graphical version (Raylib or SFML) — eventually

-----
## Author

Laurent

-----

*Coded on an iPhone with a-shell. Yes, really.*