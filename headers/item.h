#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item{
	private:
		std::string name;
		int healAmount;
	public:
		Item(std::string itemName, int hPoint);
		int healPoints (){return healAmount;}
		std::string getName(){return name;}
};
#endif