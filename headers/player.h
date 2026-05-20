#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "item.h"
#include "enemy.h"

class Player{
    private:
        std::string name;
        int maxHp, xp, hp, level, xpToNextLevel, attack, defense, gold;
        std::vector<Item> inventory;
    public:
        //constructor
        Player(std::string PlayerName);
        void saveToFile(const std::string& filename);
        bool loadFromFile(const std::string& filename);
        //getters
        int getAttack() const { return attack; }
        int getMaxHp() const {return maxHp;}
        int getDefense() const { return defense; }
        int getHp() const { return hp; }
        int getXpToNextLv() const { return xpToNextLevel; }
        int getGoldAmount() const { return gold; }
        std::string getName() const { return name; }
        bool isAlive() const { return hp > 0; }
        int getLevel() const { return level; }
        void showItems();
        //setters
        int takeDamage(int amount);
        void heal (int amout);
        void addXp(int amount);
        void addGold(int amount);
        void addDefense(int amount){defense += amount;}
        void levelUp();
        void addItem(Item item);
        void useItem(int index);
        //helpful functions
        void displayStats();
        bool runAway(bool state,bool isTakingDamage);
        std::string dialogue();
        void displayHealthBar();
};

#endif