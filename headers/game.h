#ifndef GAME_H
#define GAME_H

#include "enemy.h"
#include "player.h"
#include <array>
enum gameState{
    LAUNCHED,
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
		Enemy generateEnemy();
		std::vector<Enemy> generateWaves();
		void combatWaves();
		void saveGame();
		void loadGame();
		int choices();
		bool actions();
		void combat(bool invoked);
		void shop();
};

#endif