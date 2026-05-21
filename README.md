# Textual RPG (C++)

A turn-based terminal RPG built from scratch in C++ as a learning project for OOP and systems programming.

-----
## Features

- ✅ **Turn-based combat** with multiple enemies
- ✅ **Wave system** - fight multiple enemies in succession
- ✅ **XP & leveling** - gain experience and level up with stat increases
- ✅ **Inventory system** - collect and use healing items
- ✅ **Persistent saves** - JSON-based save system that remembers all progress
- ✅ **Dynamic difficulty** - enemies scale with player level
- ✅ **Multiple game states** - combat, victory, defeat, flee, main menu
- ✅ **Dynamic dialogue** - player responses change based on current HP %
- ✅ **Health bars** - visual feedback in combat

-----
## Game Mechanics

### Combat System
- Player and enemy take turns attacking
- Defense reduces incoming damage
- Can flee with random success chance
- Victory grants XP and gold rewards

### Progression
- Level up to increase max HP, attack, and defense
- XP threshold increases after each level
- Track gold and inventory

### Save System
- **JSON format** with full data structure
- Saves: character stats, XP, inventory, resources
- Auto-load on startup

-----
## Technical Details

### Architecture
- **OOP Design**: `Player`, `Enemy`, `Game`, `Item` classes
- **State Machine**: Enum-based game state management (`LAUNCHED`, `RUNNING`, `WON`, `DEAD`, `FLED`)
- **File I/O**: `std::fstream` + nlohmann/json library
- **Modular**: Headers/implementation separated

### Libraries
- **Standard C++11** (`<iostream>`, `<fstream>`, `<vector>`, `<array>`)
- **nlohmann/json** (header-only, auto-downloaded)

### Project Stats
- **754 lines** of custom code (headers + src + main)
- **5 source files** + **5 header files**
- **Single executable** compilation

-----
## Project Structure

```
.
├── main.cpp                     # Entry point
├── compile.sh                   # Build script
├── README.md                    # This file
├── build/
│   ├── rpg_game                 # Compiled executable
│   └── save.json                # Game save file (created at runtime)
├── headers/
│   ├── game.h
│   ├── player.h
│   ├── enemy.h
│   ├── item.h
│   └── tools.h
├── src/
│   ├── game.cpp
│   ├── player.cpp
│   ├── enemy.cpp
│   ├── item.cpp
│   └── tools.cpp
└── include/
    └── json.hpp                 # JSON library (auto-downloaded)
```

-----
## Building & Running

### Compile
```bash
g++ -Wall -Wextra -std=c++11 -I./headers -I./include main.cpp src/*.cpp -o build/rpg_game
```

### Run
```bash
./build/rpg_game
```

-----
## Game Flow

1. **Load/Create** - Load existing save or start new adventure
2. **Main Menu** - Choose: fight enemy, fight wave, check stats, manage items
3. **Combat** - Turn-based attacks, can flee or use items
4. **Resolution** - Win, lose, or flee; restart or quit
5. **Save** - Automatically saved as JSON on quit

-----
## What I Learned

This project demonstrates:
- ✅ Class design and inheritance
- ✅ Pointer/reference management
- ✅ File I/O and serialization (JSON)
- ✅ State machine patterns
- ✅ Vector operations (dynamic enemy waves)
- ✅ Game loop architecture




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

*Coded on an iPhone with a-shell. Yes, really. (now on my computer)*