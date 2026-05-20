#ifndef GAME_H
#define GAME_H

#include "enemy.h"
#include "player.h"

enum gameState{
    RUNNING,
    FLED,
    WON,
    DEAD,
};

class Game{
	private:
		gameState combatState;
		bool isRunning, rewarded,playerTurn;
		int menueType, choice, itemChoice;
		Player* player;
		Enemy* enemy;
	public:
		Game(Player& p, Enemy& e);
		void generateEnemy();
		void saveGame();
		void loadGame();
		int choices();
		bool actions();
		void combat();
		void shop();
};

#endif