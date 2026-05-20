#include "player.h"
#include <iostream>
#include "enemy.h"
#include "game.h"

int main() {
    Enemy enemy ("",1);
    Player hero("");
    Game game(hero,enemy);
    game.loadGame();
    game.generateEnemy();
    game.combat();
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}