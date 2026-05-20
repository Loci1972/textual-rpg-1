#include "enemy.h"
#include <iostream>
#include <string>
#include <numeric>

Enemy::Enemy(std::string playerName, int level_add){
    name = playerName;
    level = level_add;
    xp = 0;
    xpReward = 50 + level;
    maxHp = 120 +(level_add-1)*3;
    hp = maxHp;
    attack = 16 + (level_add-1)*3;
    defense = (level_add-1)*2;
    goldReward = 50+level ;
}


int Enemy::takeDamage(int amount){
    int actualDamage = amount - defense;
    if (actualDamage > 0){
        hp = std::max(0,hp - actualDamage);
    }
    return actualDamage;
}

void Enemy::displayHealthBar(){
    int barLength = 25;
    int filledLength = (hp * barLength) / maxHp;
    if (filledLength < 0 && hp > 0) filledLength += 1;
    std::cout << name << " [";
    for (int i = 0 ; i < barLength; i++){
        
        std::cout << (i < filledLength ? "█" : "░");

    }
    std::cout << "] " << hp << "/" << maxHp << "\n" << dialogue() << std::endl;
}

void Enemy::displayStats(){
    std::cout<<"===STATS===\n" << "Enemy: " << name 
    << "\nLevel : " << level <<"\nAttack : " << attack 
    << "\nDefense : " << defense 
    << std::endl;
    displayHealthBar();
    dialogue();
}

std::string Enemy::dialogue() { 
    int hp_percent = (100 *hp)/maxHp;
    if (hp_percent >= 90){
        return "I will kill you !" ;
    }else if (hp_percent >= 60){
        return "How can you do this !?" ;
    }else if(hp_percent >= 30){
        return "am I actually dying ?"; 
    }else if (hp_percent > 0){
        return "...";
    }else{
        return "DEAD 💀 !!!";
    }
}