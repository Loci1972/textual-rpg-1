#include "iostream"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include "tools.h"
#include <ctime>
#include <array>


Game::Game(Player& p, Enemy& e)
    : combatState(RUNNING), isRunning(true), rewarded(false),
      playerTurn(true), menueType(1), choice(0), itemChoice(0),
      player(&p), enemy(&e) {
}
void Game::saveGame(){
    player->saveToFile("save.txt");
}

void Game::loadGame(){
    if (player->loadFromFile("save.txt")) {
        std::cout << "Welcome back, " << player->getName() << "!\n";
    } else {
        std::cout << "New adventure! Enter your name: ";
        *player = Player(getString());
    }
}

int Game::choices(){
    int a;
    while (true){
        if (combatState == RUNNING){
            std::cout << " <<<MENUE>>> " << std::endl;
            std::cout << " 1. Attack\n 2. Run away\n 3. Stats\n 4. Items\n" ;
            a = getNumber();
            if (a >= 1 && a <= 4) return a;
            menueType = 1;
            std::cout << "Invalid choice !!" << std::endl;
        }else if (combatState == DEAD){
            std::cout << " <<<You Lose...>>> " << std::endl;
            std::cout << " 1. Retry\n 2. quit\n 3. Stats\n" ;
            a = getNumber();
            menueType = 2;
            if (a >= 1 && a <= 3) return a;
            std::cout << "Invalid choice !!" << std::endl;
        }else if (combatState == FLED){
            std::cout << " <<<You Ran Away 🐔...>>> " << std::endl;
            std::cout << " 1. New fight\n 2. quit\n 3. Stats\n" ;
            a = getNumber();
            menueType = 3;
            if (a >= 1 && a <= 3) return a;
            std::cout << "Invalid choice !!" << std::endl;  
        }
        else {
            std::cout << " <<<YOU WON !!!...>>> " << std::endl;
            std::cout << " 1. New fight\n 2. quit\n 3. Stats\n" ;
            a = getNumber();
            menueType = 4;
            if (a >= 1 && a <= 3) return a;
            std::cout << "Invalid choice !!" << std::endl;
        }
    }
}

bool Game::actions (){
    // Cas 1 : Le combat est en cours
    if (menueType == 1) {
        switch (choice) {
            case 1:// Attack
        std::cout << "You hit " << enemy->getName() << " with " << enemy->takeDamage(player->getAttack()) << " Damages.\n";
		enemy->displayHealthBar();
                playerTurn = false; 
                break;
            case 2: // Run away (souvent géré dans le main, mais au cas où)
                break;
            case 3: // Stats
                player->displayStats();
                break;
            case 4: // Items
                player->showItems();
                std::cout << "<<ITEMS>> \n 1. Use item\n 2. Cancel\n ? : ";
                itemChoice = getNumber();
                if (itemChoice == 1) player->useItem(getNumber());
                if (itemChoice == 2) std::cout << "canceled" << std::endl;
                break;
            }
        return true;
    } 
    // Cas 2, 3 ou 4 : Le combat est fini (Mort, Victoire ou Fuite)
    else {
        switch (choice) {
            case 1: // Restart / Continue
                player->heal(player->getMaxHp());
                enemy->fullHeal();
                playerTurn = true;
                std::cout << "Restarting...\n";
                break;
            case 2: // Quit
		player->heal(player->getMaxHp());
                saveGame();
                return false;
            case 3: // Stats
                player->displayStats();
                break;
        }
    }
    return true;
}

void Game::combat(){
    while (isRunning) {
        if (combatState != FLED){
            // --- 1. SET THE STATE AND MENU TYPE ---
            if (player->isAlive() && enemy->isAlive()){
                menueType = 1; // Combat menu
                combatState = RUNNING;
            } else if (!player->isAlive()) {
                menueType = 2; // Death menu
                combatState = DEAD;
            }else if (player->isAlive() && !enemy->isAlive()){
                menueType = 3; // Victory menu
                combatState = WON;
            }
        }else {
            menueType = 4; // Flee menu
        }
        if (combatState == WON && !rewarded){
            player->addGold(enemy->getGoldReward());
            player->addXp(enemy->getXpReward());
            rewarded = true;
        }
        // --- 2. PLAYER OR ENEMY TURN ---
        if (playerTurn) {
            // Get the choice based on the current menu
            choice = choices();
            if (menueType == 1 && choice == 2) {
                combatState = (player->runAway(randomState(), true) ? FLED : RUNNING);
                if (combatState != FLED) playerTurn = false; // Failed flee = Enemy hits you
            } else {
                // Execute options and update game state
                isRunning = actions();
                
                // If we chose "Restart" (Choice 1) in a non-combat menu
                if (menueType != 1 && choice == 1) {
                    generateEnemy();
                    combatState = RUNNING;
                    rewarded = false;
                }
                if (menueType == 2 && choice == 2){
                    generateEnemy();
                }
        }
        } else {
            // --- ENEMY TURN ---
            if (player->isAlive() && enemy->isAlive()) {
                std::cout << "\n--- " << enemy->getName() << "'s Turn ---\n";
                int dmg = player->takeDamage(enemy->getAttack());
std::cout << enemy->getName() << " deals " << dmg << " damage!\n";
                player->displayHealthBar();
            }
            playerTurn = true; // Hand over to player
        }
    }
	
}

void Game::shop(){
    std::cout << "coming soon..." << std::endl;
}

void Game::generateEnemy(){
    int playerLevel = player->getLevel();
	constexpr int default_lenght = 5;
	int index;
std::array<Enemy,default_lenght> Enemies = {
		Enemy("Dragon",playerLevel+randomInt(2,6)),
		Enemy("Spider", playerLevel+randomInt(1,3)),
		Enemy("Goblin", playerLevel+randomInt(2,3)),
		Enemy("Skeleton", playerLevel+1),
		Enemy("Zombie", playerLevel+randomInt(2,4))
	};
	index = randomInt(0,default_lenght-1);
    *enemy = Enemies[index];
    enemy -> addDefense(-3);
}