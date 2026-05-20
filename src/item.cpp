#include <string>
#include "item.h"
#include <iostream>

Item::Item(std::string itemName, int hPoint){
	name = itemName;
	healAmount = hPoint;
}