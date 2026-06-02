#include "item.h"

// Il faut que la signature corresponde exactement à ton item.h !
Item::Item(std::string itemName, int value, int itemPrice, ItemType itemType) {
    name = itemName;
    effectValue = value;
    price = itemPrice;
    type = itemType;
}