#include <random>
#include <ctime>
#include "tools.h"
#include "player.h"
#include "enemy.h"
#include <iostream>
#include <numeric>
#include <string>

int getNumber(){
    int a;
    while (true){
        if (std::cin >> a) {
            std::cin.clear();
            break;
        }else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid Input retry :( \n";
        }
    }
    return a;
}

std::string getString(){
    std::string text;
    while(text != "" || text != " "){
        std::getline(std::cin, text);
        break;
    }
    return text;
}

int realDamage(const Enemy& enemy, const Player& player, const std::string& entity){
    if (entity == "player") return std::max(0, player.getAttack() - enemy.getDefense());
    else if (entity == "enemy") return std::max(0, enemy.getAttack() - player.getDefense());
    return 0;
}

bool randomState () {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, 3); 
    int random_num = distrib(gen);
    if (random_num == 1) return true;
    else return false;
}

int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}