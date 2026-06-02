#ifndef ITEM_H
#define ITEM_H

#include <string>

enum ItemType {
    HEAL,    // Soigne les PV
    ATTACK,  // Boost l'attaque temporairement ou définitivement
    DEFENSE  // Boost la défense
};

class Item {
    private:
        std::string name;
        int effectValue; // Remplace healAmount pour être plus générique
        int price;       // Le coût d'achat au shop
        ItemType type;   // Le type d'objet
    public:
        Item(std::string itemName, int value, int itemPrice, ItemType itemType);
        std::string getName() const { return name; }
        int getValue() const { return effectValue; }
        int getPrice() const { return price; }
        ItemType getType() const { return type; }
};

#endif