#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item{
	private:
		std::string name;
		int healAmount;
	public:
		Item(std::string itemName, int hPoint);
		int healPoints() const {return healAmount;}
		std::string getName() const {return name;}
};
#endif