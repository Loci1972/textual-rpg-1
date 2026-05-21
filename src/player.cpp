#include "player.h"
#include <iostream>
#include <string>
#include <numeric>
#include "enemy.h"
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

Player::Player(std::string playerName){
    name = playerName;
    level = 1;
    xp = 0;
    xpToNextLevel = 100;
    maxHp = 120;
    hp = maxHp;
    attack = 15;
    defense = 8;
    gold = 50;
}

void Player::levelUp(){
    std::cout << "Level increased !! " << std::endl;
    level += 1;
    maxHp += 6;
    hp = maxHp;
    displayStats();
    attack += 3;
    defense += 5;
    xpToNextLevel += 50;
}

void Player::addXp(int amount){
    xp += amount;
    while (xp >= xpToNextLevel) {
        xp -= xpToNextLevel;
        levelUp();
    }
    std::cout << "you got +" << amount << " XP"<< std:: endl;
}

void Player::addGold(int amount){
    gold += amount;
    std::cout << "you got " << amount << " gold" << std::endl;
}

void Player::heal(int amount){
    if (amount + hp > maxHp){
        hp = maxHp;
    }else {
        hp += amount;
    }
}

int Player::takeDamage(int amount){
    int actualDamage = amount - defense;
    if (actualDamage > 0){
        hp = std::max(0,hp - actualDamage);
    }
    return actualDamage;
}

void Player::displayHealthBar(){
    int barLength = 25;
    int filledLength = (hp * barLength) / maxHp;
    if (filledLength < 0 && hp > 0) filledLength += 1;
    std::cout << name << " [";
    for (int i = 0 ; i < barLength; i++){
        
        std::cout << (i < filledLength ? "█" : "░");

    }
    std::cout << "] " << hp << "/" << maxHp << "\n" << dialogue() << std::endl;
}

void Player::displayStats(){
    std::cout<<"===STATS===\n" << "Player: " << name 
    << "\nLevel : " << level <<"\nAttack : " << attack 
    << "\nDefense : " << defense << "\n XP: " 
    << xp << "/" << xpToNextLevel << std::endl;
    displayHealthBar();
    dialogue();
}

bool Player::runAway(bool state,bool isTakingDamage){
    int damage_taken = 10;
    if (!state) std::cout << "you flee but you broke your leg\n";
    else if (state) std::cout << "you fled with SUCCESS !!! " << std::endl;
    if (isTakingDamage && !state) {
        std::cout << ", -" << damage_taken - defense <<"\n";
        takeDamage(damage_taken);
    }
    return state;
}



std::string Player::dialogue() { 
    int hp_percent = (100 *hp)/maxHp;
    if (hp_percent >= 90){
        return "Ez pls" ;
    }else if (hp_percent >= 50){
        return "still alive barelly..." ;
    }else if(hp_percent >= 40){
        return "why do i hear boss music ?" ; 
    }else if (hp_percent > 0){
        return "mom... pick me up I'm scrared :( ";
    }else{
        return "DEAD 💀 !!!";
    }
}

void Player::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << name << "\n"
             << level << "\n"
             << xp << "\n"
             << maxHp << "\n"
             << hp << "\n"
             << attack << "\n"
             << defense << "\n"
             << gold << "\n";
        file.close();
        std::cout << "Partie sauvegardée avec succès !\n";
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier de sauvegarde.\n";
    }
}

bool Player::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::getline(file, name);
        file >> level >> xp >> maxHp >> hp >> attack >> defense >> gold;
        file.close();
        return true;
    }
    return false; // Le fichier n'existe pas encore
}

void Player::saveToJSON(const std::string& filename) {
    try {
        json playerData;
        
        // Sauvegarder les stats du joueur
        playerData["character"]["name"] = name;
        playerData["character"]["level"] = level;
        playerData["character"]["xp"] = xp;
        playerData["character"]["xpToNextLevel"] = xpToNextLevel;
        
        // Sauvegarder la santé
        playerData["stats"]["maxHp"] = maxHp;
        playerData["stats"]["currentHp"] = hp;
        playerData["stats"]["attack"] = attack;
        playerData["stats"]["defense"] = defense;
        
        // Sauvegarder l'or
        playerData["resources"]["gold"] = gold;
        
        // Sauvegarder l'inventaire
        json inventoryArray = json::array();
        for (const auto& item : inventory) {
            json itemJson;
            itemJson["name"] = item.getName();
            itemJson["healAmount"] = item.healPoints();
            inventoryArray.push_back(itemJson);
        }
        playerData["inventory"] = inventoryArray;
        
        // Ajouter des métadonnées
        playerData["metadata"]["version"] = "1.0";
        playerData["metadata"]["savedAt"] = "Game Save";
        
        // Écrire dans le fichier avec indentation
        std::ofstream file(filename);
        if (file.is_open()) {
            file << playerData.dump(4); // dump(4) = indentation de 4 espaces
            file.close();
            std::cout << "✅ Partie sauvegardée avec succès en JSON !\n";
        } else {
            std::cerr << "❌ Erreur : Impossible d'ouvrir le fichier de sauvegarde JSON.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "❌ Erreur lors de la sauvegarde JSON : " << e.what() << "\n";
    }
}

bool Player::loadFromJSON(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (file.is_open()) {
            json playerData;
            file >> playerData;
            file.close();
            
            // Charger les stats du joueur
            name = playerData["character"]["name"];
            level = playerData["character"]["level"];
            xp = playerData["character"]["xp"];
            xpToNextLevel = playerData["character"]["xpToNextLevel"];
            
            // Charger la santé
            maxHp = playerData["stats"]["maxHp"];
            hp = playerData["stats"]["currentHp"];
            attack = playerData["stats"]["attack"];
            defense = playerData["stats"]["defense"];
            
            // Charger l'or
            gold = playerData["resources"]["gold"];
            
            // Charger l'inventaire
            inventory.clear();
            if (playerData.contains("inventory") && playerData["inventory"].is_array()) {
                for (const auto& itemJson : playerData["inventory"]) {
                    std::string itemName = itemJson["name"];
                    int healAmount = itemJson["healAmount"];
                    inventory.emplace_back(itemName, healAmount);
                }
            }
            
            std::cout << "✅ Partie chargée avec succès depuis JSON !\n";
            return true;
        }
        return false;
    } catch (const std::exception& e) {
        std::cerr << "❌ Erreur lors du chargement JSON : " << e.what() << "\n";
        return false;
    }
}

void Player::addItem(Item item) {
    inventory.push_back(item);
}

void Player::useItem(int index) {
    if (index >= 1 && (size_t)index <= inventory.size()) {  // ✅ <= au lieu de <
        Item& it = inventory[index-1];  // ✅ index-1 !
        heal(it.healPoints());
        std::cout << "Used " << it.getName() << " - healed " 
                  << it.healPoints() << " HP\n";
        inventory.erase(inventory.begin() + (index-1));
    } else {
        std::cout << "Invalid choice!" << std::endl;
    }
}

void Player::showItems(){
    int inventorySize = inventory.size();
    std::cout << "==" <<"Items" << "==" << std::endl;
    for (int i = 1; i < inventorySize + 1; i++){
        int itemIndex = i - 1;
        std::cout << i <<"|"<< inventory[itemIndex].getName() << std::endl;
    }
}