#include "iostream"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include "tools.h"
#include <ctime>
#include <array>
#include <vector>

Game::Game(Player& p, Enemy& e)
    : combatState(LAUNCHED), isRunning(true), rewarded(false),
      playerTurn(true), menueType(1), choice(0), itemChoice(0),
      player(&p), enemy(&e) {
}
void Game::saveGame(){
    player->saveToJSON("save.json");
}

void Game::loadGame(){
    if (player->loadFromJSON("save.json")) {
        std::cout << "Welcome back, " << player->getName() << "!\n";
    } else {
        std::cout << "New adventure! Enter your name: ";
        *player = Player(getString());
    }
}

int Game::choices(){
    int a;
    while (true){
        if (combatState == LAUNCHED){
            std::cout << " <<<MENUE>>> " << std::endl;
            std::cout << " 1. fight enemy\n 2. fight wave\n 3. Stats\n 4. Items\n";
            a = getNumber();
            if (a >= 1 && a <= 4) return a;
            menueType = 1;
            std::cout << "Invalid choice !!" << std::endl;
        }else if (combatState == RUNNING){
            std::cout << " <<<In combat>>> " << std::endl;
            std::cout << " 1. Attack\n 2. Run away\n 3. Stats\n 4. Items\n" ;
            a = getNumber();
            if (a >= 1 && a <= 4) return a;
            menueType = 2;
            std::cout << "Invalid choice !!" << std::endl;
        }else if (combatState == DEAD){
            std::cout << " <<<You Lose...>>> " << std::endl;
            std::cout << " 1. Retry\n 2. quit\n 3. Stats\n" ;
            a = getNumber();
            menueType = 3;
            if (a >= 1 && a <= 3) return a;
            std::cout << "Invalid choice !!" << std::endl;
        }else if (combatState == FLED){
            std::cout << " <<<You Ran Away 🐔...>>> " << std::endl;
            std::cout << " 1. New fight\n 2. quit\n 3. Stats\n" ;
            a = getNumber();
            menueType = 4;
            if (a >= 1 && a <= 3) return a;
            std::cout << "Invalid choice !!" << std::endl;  
        }
        else {
            std::cout << " <<<YOU WON !!!...>>> " << std::endl;
            std::cout << " 1. New fight\n 2. quit\n 3. Stats\n" ;
            a = getNumber();
            menueType = 5;
            if (a >= 1 && a <= 3) return a;
            std::cout << "Invalid choice !!" << std::endl;
        }
    }
}

bool Game::actions (){
    if (menueType == 1) {
        switch (choice) {
            case 1:
                combatState = RUNNING;
                break;
            case 2:
                combatWaves();
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
    } else if (menueType == 2) {
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
    // Cas 3, 4 ou 5 : Le combat est fini (Mort, Victoire ou Fuite)
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

void Game::combat(bool invoked){
    while (isRunning) {
        stateManager(invoked);
        // --- 2. PLAYER OR ENEMY TURN ---
        if (playerTurn) {
            // Get the choice based on the current menu
            choice = choices();
            if (menueType == 2 && choice == 2) {
                combatState = (player->runAway(randomState(), true) ? FLED : RUNNING);
                if (combatState != FLED) playerTurn = false; // Failed flee = Enemy hits you
            } else {
                // Execute options and update game state
                isRunning = actions();
                
                // If we chose "Restart" (Choice 1) in a non-combat menu
                if ((menueType != 1 && menueType != 2) && choice == 1) {
                    generateEnemy();
                    combatState = RUNNING;
                    rewarded = false;
                }
                if (menueType == 3 && choice == 2){
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

void Game::stateManager(bool invoked){
    if (combatState != FLED && combatState != LAUNCHED){
    // --- 1. SET THE STATE AND MENU TYPE ---
    if (player->isAlive() && enemy->isAlive()){
        menueType = 2; // Combat menu
        combatState = RUNNING;
    } else if (!player->isAlive()) {
        menueType = 3; // Death menu
        combatState = DEAD;
        if (invoked) isRunning = false;
    }else if (player->isAlive() && !enemy->isAlive()){
        menueType = 4; // Victory menu
        combatState = WON;
        if (invoked) isRunning = false;
    }
    }else if (combatState == FLED){
        menueType = 5; // Flee menu
        if (invoked) isRunning = false;
    }if (combatState == WON && !rewarded){
        player->addGold(enemy->getGoldReward());
        player->addXp(enemy->getXpReward());
        rewarded = true;
        if (invoked) isRunning = false;
    }
}

void Game::shop(){
    std::cout << "coming soon..." << std::endl;
}

Enemy Game::generateEnemy(){
    int playerLevel = player->getLevel();
	constexpr int default_lenght = 6;
	int index;
std::array<Enemy,default_lenght> Enemies = {
		Enemy("Dragon",playerLevel+3),
		Enemy("Spider", playerLevel+1),
		Enemy("Goblin", playerLevel+1),
		Enemy("Skeleton", playerLevel),
		Enemy("Zombie", playerLevel+1),
        Enemy("mouton",playerLevel+1),
	};
	index = randomInt(0,default_lenght-1);
    *enemy = Enemies[index];
    enemy -> addDefense(-3);
    return Enemy(*enemy);
}

std::vector<Enemy> Game::generateWaves(){
    std::vector<Enemy> enemies;
    int waveSize = 10;
    for (int i = 0; i < waveSize ; i++){
        enemies.push_back(generateEnemy());
    }
    return enemies;
}

void Game::combatWaves(){
    std::vector<Enemy> enemies = generateWaves();
    size_t selectedEnemy = 0;
    
    while (!enemies.empty() && player->isAlive()) {
        // Afficher la liste
        std::cout << "\n=== WAVE - Remaining enemies: " << enemies.size() << " ===\n";
        for (size_t i = 0; i < enemies.size(); i++){
            std::cout << i+1 << "| " << enemies[i].getName() << std::endl;
        }
        
        std::cout << "Select an enemy (or 0 to go back): ";
        size_t input = (size_t)getNumber();
        
        if (input == 0) break; // Quitter la vague
        
        if (input >= 1 && input <= enemies.size()){
            selectedEnemy = input - 1;
            enemies[selectedEnemy].displayStats();
            std::cout << "Fight this enemy? 1.Yes  2.No\n ? : ";
            input = getNumber();
            
            if (input == 1){
                *enemy = enemies[selectedEnemy];
                combatState = RUNNING;
                rewarded = false;
                isRunning = true;
                combat(true);
                
                // Si ennemi vaincu, le retirer de la liste
                if (!enemy->isAlive()) {
                    enemies.erase(enemies.begin() + selectedEnemy);
                    std::cout << "Enemy defeated! Next...\n";
                }
                combatState = LAUNCHED;
                isRunning = true;  
            }
        }
    }
    
    if (enemies.empty()) {
        std::cout << "\n🎉 Wave completed!\n";
    }
    combatState = WON;
}