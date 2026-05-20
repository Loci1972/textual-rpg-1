#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <string>
#include <algorithm>

class Enemy{
    private:
        std::string name;
        int maxHp, xp, hp, level, xpReward, attack, defense, goldReward;
    public:
        //constructor
        Enemy(std::string PlayerName, int level_add);
        //getters
        int getLevel() const { return level; }
        int getAttack() const { return attack; }
        int getMaxHp() const {return maxHp;}
        int getDefense() const { return defense; }
        int getXpReward() const {return xpReward ;}
        int getHp() const { return hp; }
        int getGoldReward() const { return goldReward; }
        bool isAlive() const { return hp > 0; }
        std::string getName() const { return name; }
        //setters
        int takeDamage(int amount);
        void addDefense(int amount){defense += amount;}
        void levelUp();
        void fullHeal () {hp = maxHp;}
        //helpful functions
        void displayStats();
        std::string dialogue();
        void displayHealthBar();
};

#endif